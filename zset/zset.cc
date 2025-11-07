#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <sw/redis++/redis.h>
#include <utility>
#include <vector>

// zadd && zrange
void test1(sw::redis::Redis& client)
{
    client.flushall();

    std::vector<std::pair<std::string, double>> kvs = {{"zhangsan", 99.9}, {"lisi", 68.2}, {"wangwu", 34.3}};
    client.zadd("key1", kvs.begin(), kvs.end());
 
    std::vector<std::string> result;
    client.zrange("key1", 0, -1, std::back_inserter(result));
    for(auto &e : result) {
        std::cout << e << std::endl;
    }

    std::vector<std::pair<std::string, double>> with_score;
    client.zrange("key1", 0, -1, std::back_inserter(with_score));
    for(auto &[x, y] : with_score) {
        std::cout << x << " " << y << std::endl;
    }
}

// zcard && zrem && zscore && zrank
void test2(sw::redis::Redis& client)
{
    client.flushall();

    std::vector<std::pair<std::string, double>> kvs = {{"zhangsan", 99.9}, {"lisi", 68.2}, {"wangwu", 34.3}};
    client.zadd("key1", kvs.begin(), kvs.end());

    std::cout << client.zcard("key1") << std::endl;

    client.zrem("key1", "zhangsan");
    std::cout << client.zcard("key1") << std::endl;

    auto score = client.zscore("key1", "lisi");
    if(score) {
        std::cout << score.value() << std::endl;
    } else {
        std::cout << "score无效" << std::endl;
    }

    auto rank = client.zrank("key1", "lisi");
    if(rank) {
        std::cout << rank.value() << std::endl;
    } else {
        std::cout << "rank无效" << std::endl;
    }
}

int main()
{
    sw::redis::Redis client("tcp://127.0.0.1:6379");
    // test1(client);
    test2(client);
    return 0;
}