#include <chrono>
#include <hiredis/hiredis.h>
#include <iostream>
#include <random>
#include <uuid/uuid.h>
#include <vector>
#include <iomanip>

class RedisDataFrameManager {
public:
    RedisDataFrameManager(const std::string& host, int port,int64_t ring_buffer_size=int64_t(1e5))
    : ring_buffer_size_(ring_buffer_size)
    {
        context_ = redisConnect(host.c_str(), port);
        if (context_ == NULL || context_->err) {
            if (context_) {
                std::cout << "Error: " << context_->errstr << std::endl;
                redisFree(context_);
            } else {
                std::cout << "Error: Can't allocate redis context" << std::endl;
            }
        }
    }

    ~RedisDataFrameManager()
    {
        if (context_) {
            redisFree(context_);
        }
    }

    void addDataToRingbuffer(const std::string& serialized_data, std::string buff) {
        redisReply *reply;
        std::string cmd = "LLEN " + buff;
        reply = (redisReply *)redisCommand(context_, cmd.c_str());
        int64_t length = reply->integer;
        freeReplyObject(reply);
        if (length >= ring_buffer_size_) {
            cmd.clear();
            cmd = "LPOP " + buff;
            reply = (redisReply *)redisCommand(context_, cmd.c_str());
            // reply = (redisReply *)redisCommand(context_, "LPOP ring_buff");
            freeReplyObject(reply);
        }
        cmd.clear();
        cmd = "LPUSH " + buff + " %b";
        reply = (redisReply *)redisCommand(context_, cmd.c_str(), serialized_data.c_str(), serialized_data.size());
        // reply = (redisReply *)redisCommand(context_, "LPUSH ring_buff %b", serialized_data.c_str(), serialized_data.size());
        freeReplyObject(reply);
        return;
    }

    void storeDataFrame(const std::string& data_frame)
    {
        uuid_t uuid;
        uuid_generate(uuid);
        char uuid_str[37];
        uuid_unparse_lower(uuid, uuid_str);
        std::string data_frame_id(uuid_str);
        const char* cString = data_frame.data();
        redisReply* reply = (redisReply*)redisCommand(context_, 
            "SETRANGE %s %llu %b", data_frame_id.c_str(), 0, cString, data_frame.size()); 
        freeReplyObject(reply);
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count();
        reply = (redisReply*)redisCommand(
            context_, "ZADD global_index %d %s", timestamp, data_frame_id.c_str());
        freeReplyObject(reply);
    }
    void saveDataFrames(const RobotDataFrameList& data_frames)
    {
        std::string str;
        data_frames.SerializeToString(&str);
        storeDataFrame(str);
    }

    std::vector<std::string> getDataFramesByGlobalIndex(int start, int end)
    {
        redisReply* reply = (redisReply*)redisCommand(
            context_, "ZRANGEBYSCORE global_index %d %d", start, end);
        std::vector<std::string> data_frame_ids;
        for (size_t i = 0; i < reply->elements; i++) {
            data_frame_ids.push_back(reply->element[i]->str);
        }
        freeReplyObject(reply);

        std::vector<std::string> data_frames;
        for (const auto& data_frame_id : data_frame_ids) {
            reply = (redisReply*)redisCommand(context_, "GET %s", data_frame_id.c_str());
            data_frames.push_back(reply->str);
            freeReplyObject(reply);
        }

        return data_frames;
    }

    std::string getRandomDataFrame()
    {
        redisReply* reply = (redisReply*)redisCommand(context_, "ZCARD global_index");
        int num_elements = reply->integer;
        freeReplyObject(reply);

        if (num_elements == 0) {
            return "";
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, num_elements - 1);
        int random_index = dis(gen);

        reply = (redisReply*)redisCommand(
            context_, "ZRANGE global_index %d %d", random_index, random_index);
        if (reply == NULL || reply->type != REDIS_REPLY_ARRAY || reply->elements < 1) {
            freeReplyObject(reply);
            return "";
        }
        std::string data_frame_id = reply->element[0]->str;
        freeReplyObject(reply);

        reply = (redisReply*)redisCommand(context_, "GET %s", data_frame_id.c_str());
        std::string data_frame;
        if (reply != NULL && reply->type == REDIS_REPLY_STRING) {
            data_frame = reply->str;
            freeReplyObject(reply);
        } else {
            return "";
        }

        return data_frame;
    }

private:
    redisContext* context_;
    int ring_buffer_size_;
};
