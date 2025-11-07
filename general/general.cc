#include <iostream>
#include <iterator>
#include <sw/redis++/redis++.h>
#include <thread>

// get && set
void test1(sw::redis::Redis& client)
{
    client.flushall();
    client.set("key1", "111");
    client.set("key2", "222");

    auto value1 = client.get("key1");
    if(value1) {
        std::cout << "value1=" << value1.value() << std::endl;
    }
    auto value2 = client.get("key2");
    if(value2) {
        std::cout << "value2=" << value2.value() << std::endl;
    }
    auto value3 = client.get("key3");
    if(value3) {
        std::cout << "value3=" << value3.value() << std::endl;
    }
}

// exists
void test2(sw::redis::Redis& client)
{
    client.flushall();
    client.set("key1", "111");
    client.set("key2", "222");

    auto ret = client.exists({"key1", "key2", "key3"}); // 返回存在key的个数
    std::cout << ret << std::endl; 
}

// del
void test3(sw::redis::Redis& client)
{
    client.flushall();
    client.set("key1", "111");
    client.set("key2", "222");

    auto ret = client.del({"key1", "key2", "key3"}); // 返回成功删除key的个数
    std::cout << ret << std::endl;
}

// keys
void test4(sw::redis::Redis& client)
{
    client.flushall();
    client.set("key1", "111");
    client.set("key2", "222");

    std::vector<std::string> result;
    client.keys("*", std::back_inserter(result));
    for(auto &e : result) {
        std::cout << e << std::endl;
    }
}

// expire && ttl
void test5(sw::redis::Redis& client)
{
    using namespace std::chrono_literals;

    client.flushall();
    client.set("key1", "111");
    client.expire("key1", 10s);

    std::this_thread::sleep_for(3s);

    auto ret = client.ttl("key1"); // 返回剩余的过期时间
    std::cout <<  ret << std::endl;
}

// type
void test6(sw::redis::Redis& client)
{
    client.flushall();
    client.set("key1", "111");
    std::string type1 = client.type("key1");
    std::cout << type1 << std::endl;

    client.lpush("key2", {10, 20, 30});
    std::string type2 = client.type("key2");
    std::cout << type2 << std::endl;

    client.hset("key3", "nickname", "baiyahua");
    std::string type3 = client.type("key3");
    std::cout << type3 << std::endl;
}

int main()
{
    sw::redis::Redis client("tcp://127.0.0.1:6379");
    // test1(client);
    // test2(client);
    // test3(client);
    // test4(client);
    // test5(client);
    test6(client);
    return 0;
}