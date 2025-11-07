#include <iostream>
#include <iterator>
#include <string>
#include <sw/redis++/command_options.h>
#include <sw/redis++/redis++.h>
#include <sw/redis++/redis.h>
#include <thread>
#include <utility>
#include <vector>

// set && get
void test1(sw::redis::Redis& client)
{
    using namespace std::chrono_literals;

    client.flushall();
    client.set("key1", "111");

    auto value1 = client.get("key1");
    if(value1) {
        std::cout << value1.value() << std::endl;
    }

    client.set("key2", "222", 5s);
    std::this_thread::sleep_for(2s);
    std::cout << client.ttl("key2") << std::endl;

    client.set("key3", "333", 0s, sw::redis::UpdateType::NOT_EXIST); // key不存在才设置
    auto value3 = client.get("key3");
    if(value3) {
        std::cout << value3.value() << std::endl;
    }

    client.set("key1", "444", 0s, sw::redis::UpdateType::EXIST); // key存在才设置
    auto value4 = client.get("key1");
    if(value4) {
        std::cout << value4.value() << std::endl;
    }
}

// mset && mget
void test2(sw::redis::Redis& client)
{
    client.flushall();

    std::vector<std::pair<std::string, std::string>> keys = {{"key1", "111"}, {"key2", "222"}, {"key3", "333"}};
    client.mset(keys.begin(), keys.end());

    std::vector<sw::redis::OptionalString> result;
    client.mget({"key1", "key2", "key3", "key4"}, std::back_inserter(result));
    for(auto &e : result) {
        if(e) {
            std::cout << e.value() << std::endl;
        } else {
            std::cout << "key无效" << std::endl;
        }
    }
}

// getrange && setrange
void test3(sw::redis::Redis& client)
{
    client.flushall();

    client.setrange("key1", 0, "abcdefg");
    auto result = client.getrange("key1", 0, -1);
    std::cout << result << std::endl;
}

// incr && decr
void test4(sw::redis::Redis& client)
{
    client.flushall();
    
    client.set("key1", "100");
    long long r1 = client.incr("key1");
    std::cout << r1 << std::endl;

    long long r2 = client.decr("key1");
    std::cout << r2 << std::endl;
}

int main()
{
    sw::redis::Redis client("tcp://127.0.0.1:6379");
    // test1(client);
    // test2(client);
    // test3(client);
    test4(client);
    return 0;
}