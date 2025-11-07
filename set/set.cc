#include <iostream>
#include <iterator>
#include <set>
#include <sw/redis++/redis.h>

// sadd && smembers
void test1(sw::redis::Redis& client)
{
    client.flushall();

    client.sadd("key1", {"111", "222", "333"});

    std::set<std::string> result;
    client.smembers("key1", std::inserter(result, result.end()));
    for(auto &e : result) {
        std::cout << e << std::endl;
    }
}

// sismember && spop && scard
void test2(sw::redis::Redis& client)
{
    client.flushall();

    client.sadd("key1", {"111", "222", "333"});

    std::cout << client.sismember("key1", "111") << std::endl;
    std::cout << client.sismember("key1", "444") << std::endl;

    std::cout << client.scard("key1") << std::endl;

    auto result = client.spop("key1");
    if(result) {
        std::cout << result.value() << std::endl;
    }
}

// sinter && sinterstore
void test3(sw::redis::Redis& client)
{
    client.flushall();

    client.sadd("key1", {"111", "222", "333", "444"});
    client.sadd("key2", {"333", "444", "555", "666"});

    std::set<std::string> result;
    client.sinter({"key1", "key2"}, std::inserter(result, result.end()));
    for(auto &e : result) {
        std::cout << e << std::endl;
    }

    long long cnt = client.sinterstore("key3", {"key1", "key2"});
    std::cout << cnt << std::endl;

    std::set<std::string> r;
    client.smembers("key3", std::inserter(r, r.end()));
    for(auto &e : r) {
        std::cout << e << std::endl;
    }
}

int main()
{
    sw::redis::Redis client("tcp://127.0.0.1:6379");
    // test1(client);
    // test2(client);
    test3(client);
    return 0;
}