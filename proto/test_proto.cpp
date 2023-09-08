//
// Created by viruser on 2023/6/28.
//

#include <iostream>
#include "test.pb.h"

int main() {
    const google::protobuf::DescriptorPool* descriptor_pool = google::protobuf::DescriptorPool::generated_pool();
    const google::protobuf::Descriptor* descriptor = descriptor_pool->FindMessageTypeByName("tutorial.Person");

    if (descriptor) {
        // 通过反射工厂和描述符创建消息实例
        const google::protobuf::Message* message = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor)->New();

        std::cout << "Message type name: " << descriptor->full_name() << std::endl;
        std::cout << "Message instance: " << message->GetTypeName() << std::endl;

        // 注意：这里你可以使用 message 进行操作
    } else {
        std::cout << "Message type not found" << std::endl;
    }
    return 0;
}
