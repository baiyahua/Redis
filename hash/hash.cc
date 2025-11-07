#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <sw/redis++/redis.h>
#include <utility>
#include <vector>

// hset && hget
void test1(sw::redis::Redis& client)
{
    client.flushall();

    std::vector<std::pair<std::string, std::string>> kvs = {{"k1", "111"}, {"k2", "222"}};
    client.hset("key1", kvs.begin(), kvs.end());
    auto result = client.hget("key1", "k1");
    if(result) {
        std::cout << result.value() << std::endl;
    }
}

// exists && hdel && hlen
void test2(sw::redis::Redis& client)
{
    client.flushall();

    std::vector<std::pair<std::string, std::string>> kvs = {{"k1", "111"}, {"k2", "222"}};
    client.hset("key1", kvs.begin(), kvs.end());
    
    std::cout << client.hexists("key1", "k1") << std::endl;
    std::cout << client.hexists("key1", "k3") << std::endl;;

    std::cout << client.hlen("key1") << std::endl;

    client.hdel("key1", "k1");
    std::cout << client.hexists("key1", "k1") << std::endl;
}

// hkeys && hvals && hmset && hmget
void test3(sw::redis::Redis& client)
{
    client.flushall();

    std::vector<std::pair<std::string, std::string>> kvs = {{"k1", "111"}, {"k2", "222"}};
    client.hset("key1", kvs.begin(), kvs.end());

    std::vector<std::string> result1;
    client.hkeys("key1", std::back_inserter(result1));
    for(auto &e : result1) {
        std::cout << e << std::endl;
    }

    std::vector<std::string> result2;
    client.hvals("key1", std::back_inserter(result2));
    for(auto &e : result2) {
        std::cout << e << std::endl;
    }


    client.hmset("key2", {
        std::make_pair("k1", "111"),
        std::make_pair("k2", "222")
    });

    std::vector<std::string> result3;
    client.hmget("key2", {"k1", "k2"}, std::back_inserter(result3));
    for(auto &e : result3) {
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