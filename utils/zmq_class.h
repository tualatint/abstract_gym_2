#include <zmq.hpp>
#include "../datatype/robot_data.pb.h"  // Include the generated header file from the .proto definition
#include <string>
#include <iostream>
#include <unistd.h>

class ZmqCppCommunication {
private:
    zmq::context_t context;
    zmq::socket_t socket;

public:
    ZmqCppCommunication(const std::string& address="127.0.0.1", int port=5555) : context(1), socket(context, ZMQ_REQ) {
        std::string connection = "tcp://" + address + ":" + std::to_string(port);
        socket.connect(connection);
    }

    std::string sendRobotData(const RobotData& robotData) {
        std::string serializedData;
        robotData.SerializeToString(&serializedData);

        zmq::message_t request(serializedData.size());
        memcpy(request.data(), serializedData.c_str(), serializedData.size());
        socket.send(request);

        zmq::message_t reply;
        socket.recv(&reply);

        return std::string(static_cast<char*>(reply.data()), reply.size());
    }

    void close() {
        socket.close();
        context.close();
    }
};