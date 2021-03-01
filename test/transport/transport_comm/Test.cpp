#include "SerialComm.hpp"
#include "CustomComm.hpp"

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

#include <gtest/gtest.h>

template <typename T>
class TransportComm : public testing::Test
{
public:
    T transport;
};

typedef testing::Types<SerialComm, CustomComm> TransportTypes;

TYPED_TEST_SUITE(TransportComm, TransportTypes, );

TYPED_TEST(TransportComm, SingleWriteReadTest)
{
    uint8_t output_msg[3] = {11, 11, 89};
    uint8_t* input_msg;
    size_t input_msg_len;

    /* Send message. */
    ASSERT_TRUE(this->transport.master_.comm.send_msg(&this->transport.master_, output_msg, sizeof(output_msg)));

    /* Receive message. */
    ASSERT_TRUE(this->transport.slave_.comm.recv_msg(&this->transport.slave_, &input_msg, &input_msg_len, 10));
    ASSERT_EQ(memcmp(output_msg, input_msg, sizeof(output_msg)), 0);
    ASSERT_FALSE(this->transport.slave_.comm.recv_msg(&this->transport.slave_, &input_msg, &input_msg_len, 10));
}

// TEST_F(TransportComm, MultiWriteReadTest)
// {
//     ASSERT_EQ(init(), 0);
//     uint16_t msgs_size = 1;
//     uint8_t output_msg[3] = {11, 11, 89};
//     uint8_t* input_msg;
//     size_t input_msg_len;

//     /* Send messages. */
//     for (int i = 0; i < msgs_size; ++i)
//     {
//         ASSERT_TRUE(master_.comm.send_msg(&master_, output_msg, sizeof(output_msg)));
//     }

//     /* Receive messages. */
//     for (int i = 0; i < msgs_size; ++i)
//     {
//         ASSERT_TRUE(slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10));
//         ASSERT_EQ(memcmp(output_msg, input_msg, sizeof(output_msg)), 0);
//     }
//     ASSERT_FALSE(slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10));
// }

// TEST_F(TransportComm, SingleOctetTest)
// {
//     ASSERT_EQ(init(), 0);
//     uint8_t output_msg = 0;
//     uint8_t* input_msg;
//     size_t input_msg_len;

//     /* Send messages. */
//     ASSERT_TRUE(master_.comm.send_msg(&master_, &output_msg, 1));

//     /* Receive message. */
//     ASSERT_TRUE(slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10));
//     ASSERT_EQ(input_msg_len, size_t(1));
//     ASSERT_EQ(*input_msg, 0);
// }

// TEST_F(TransportComm, NoPayloadTest)
// {
//     ASSERT_EQ(init(), 0);
//     uint8_t output_msg = 0;

//     /* Send messages. */
//     ASSERT_FALSE(master_.comm.send_msg(&master_, &output_msg, 0));
// }


// TEST_F(TransportComm, WorstStuffingTest)
// {
//     ASSERT_EQ(init(), 0);
//     uint8_t output_msg[UXR_CONFIG_SERIAL_TRANSPORT_MTU];
//     uint8_t* input_msg;
//     size_t input_msg_len;

//     memset(output_msg, UXR_FRAMING_BEGIN_FLAG, sizeof(output_msg));
//     ASSERT_TRUE(master_.comm.send_msg(&master_, output_msg, sizeof(output_msg)));

//     ASSERT_TRUE(slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 100));
//     ASSERT_EQ(memcmp(output_msg, input_msg, sizeof(output_msg)), 0);
// }

// TEST_F(TransportComm, FatigueTest)
// {
//     ASSERT_EQ(init(), 0);
//     uint16_t msgs_size = uint16_t(~0);
//     uint16_t sent_counter = 0;
//     uint16_t recv_counter = 0;
//     uint8_t receiver_ratio = 8;
//     uint8_t output_msg[UXR_CONFIG_SERIAL_TRANSPORT_MTU];
//     uint8_t* input_msg;
//     size_t input_msg_len;

//     for (size_t i = 0; i < sizeof(output_msg); ++i)
//     {
//         output_msg[i] = uint8_t(i % (std::numeric_limits<uint8_t>::max() + 1));
//     }

//     for (uint16_t i = 0; i < msgs_size; ++i)
//     {
//         size_t output_len = (i % sizeof(output_msg));
//         if (master_.comm.send_msg(&master_, output_msg, output_len))
//         {
//             ++sent_counter;
//         }

//         if (i % receiver_ratio == 0)
//         {
//             if (slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10))
//             {
//                 ++recv_counter;
//             }
//         }
//     }

//     while (slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10))
//     {
//         ++recv_counter;
//     }

//     ASSERT_EQ(recv_counter, sent_counter);
// }

// TEST_F(TransportComm, SplitMessageTest)
// {
//     ASSERT_EQ(init(), 0);

//     uint8_t* input_msg;
//     size_t input_msg_len;
//     uint8_t output_msg[] = {0, 1, 1, 0, 0, 0, 0};
//     uint8_t flag = UXR_FRAMING_BEGIN_FLAG;

//     /* Send BEGIN flag. */
//     ASSERT_EQ(write(slave_.platform.poll_fd.fd, static_cast<void*>(&flag), 1), 1);

//     /* Send PAYLOAD. */
//     for (size_t i = 0; i < sizeof(output_msg); ++i)
//     {
//         ASSERT_FALSE(slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10));
//         ASSERT_EQ(write(slave_.platform.poll_fd.fd, static_cast<void*>(&output_msg[i]), 1), 1);
//     }

//     ASSERT_TRUE(slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10));
//     ASSERT_EQ(input_msg_len, size_t(1));
//     ASSERT_EQ(*input_msg, 0);
// }

// TEST_F(TransportComm, NoiseTest)
// {
//     ASSERT_EQ(init(), 0);

//     uint8_t* input_msg;
//     size_t input_msg_len;
//     uint8_t output_msg[3] = {11, 11, 89};
//     uint8_t tmp_buffer[100];

//     ASSERT_TRUE(master_.comm.send_msg(&master_, output_msg, sizeof(output_msg)));
//     ssize_t bytes_read = read(fd_, tmp_buffer, sizeof(tmp_buffer));
//     ASSERT_GT(bytes_read, 0);
//     ssize_t bytes_written = write(fd_, tmp_buffer, size_t(bytes_read));
//     ASSERT_EQ(bytes_read, bytes_written);
//     ASSERT_TRUE(slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10));

//     /* Write/Read WITH noise message. */
//     ASSERT_TRUE(master_.comm.send_msg(&master_, output_msg, sizeof(output_msg)));
//     bytes_read = read(fd_, tmp_buffer, sizeof(tmp_buffer));
//     ASSERT_GT(bytes_read, 0);
//     tmp_buffer[4] = uint8_t(tmp_buffer[4] + 1);
//     bytes_written = write(fd_, tmp_buffer, size_t(bytes_read));
//     ASSERT_EQ(bytes_read, bytes_written);
//     ASSERT_FALSE(slave_.comm.recv_msg(&slave_, &input_msg, &input_msg_len, 10));
// }
