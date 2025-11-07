#include <iostream>
#include <iterator>
#include <sw/redis++/redis.h>
#include <vector>

// lpush && lrange
void test1(sw::redis::Redis& client)
{
    client.flushall();

    client.lpush("key1", {"111", "222", "333", "444"});
    std::vector<std::string> result;
    client.lrange("key1", 0, -1, std::back_inserter(result));
    for(auto &e : result) {
        std::cout << e << std::endl;
    }
}

// rpush && lpop && rpop
void test2(sw::redis::Redis& client)
{
    client.flushall();

    client.rpush("key1", {"111", "222", "333", "444"});

    auto v1 = client.lpop("key1");
    if(v1) {
        std::cout << v1.value() << std::endl;
    }

    auto v2 = client.rpop("key1");
    if(v2) {
        std::cout << v2.value() << std::endl;
    }
}

// blpop
void test3(sw::redis::Redis& client)
{
    using namespace std::chrono_literals;

    client.flushall();

    // OptionalStringPair -> std::optional<std::pair<std::string, std::string>> 
    // first->值来自哪个key second->值
    sw::redis::OptionalStringPair result =  client.blpop("key1", 10s);
    if(result) {
        std::cout << result->first << std::endl;
        std::cout << result->second << std::endl;
    } else {
        std::cout << "result无效" << std::endl;
    }
}

// llen
void test4(sw::redis::Redis& client)
{
    client.flushall();

    client.lpush("key1", {"111", "222", "333"});
    std::cout << client.llen("key1") << std::endl;
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