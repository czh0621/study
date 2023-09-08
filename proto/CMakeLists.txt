
# 指定要使用的 Protobuf 版本
find_package(Protobuf REQUIRED)

# 指定要编译的 .proto 文件
set(PROTO_FILES test.proto)

# 生成对应的 .pb.cc 和 .pb.h 文件
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})


include_directories("../cmake-build-debug/proto")

# 添加生成的源文件到项目中
add_executable(s_test_proto test_proto.cpp ${PROTO_SRCS} ${PROTO_HDRS})



# 指定链接 Protobuf 库
target_link_libraries(s_test_proto protobuf::libprotobuf)
