#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <execution>
#include <syncstream>
#include <cstdint>

void useRange_for_each()
{
	struct Custom
	{
	private:
		double value_;
	public:
		explicit Custom(double value) : value_(value) {}

		double getValue() const { return value_ + 1;}
	};

	std::vector<Custom> data(10, Custom{1.0});

	double sum = 0;
	std::ranges::for_each(data, [&sum](auto v) {sum += v;}, &Custom::getValue);
	std::cout << sum << '\n'; // 20

	auto getValue = [](const Custom& v) -> double
	{
		return 3;
	};
	double sum1 = 0;
	std::ranges::for_each(data, [&sum1](auto v) {sum1 += v;}, getValue);
	std::cout << sum1 << '\n'; // 30
}



constexpr inline size_t MAIN_SEATS = 8;
constexpr inline size_t PAGE_SIZE = 5;

struct Player
{
	int score = 0;
	std::string display_name;
};

auto get_rankings() -> std::vector<Player>
{
	return {
	   {20, "Player 1"}, {21, "Player 2"}, {23, "Player 3"}, {19, "Player 4"}, {5, "Player 5"},
	   {18, "Player 6"}, {17, "Player 7"}, {25, "Player 8"}, {24, "Player 9"}, {3, "Player 10"},
	};
}

void send_invitation_to_main_tournament(const Player& player) {
    std::osyncstream(std::cout) << "Inviting " << player.display_name << " to the main tournament.\n";
}

void store_final_score(int page, const std::string& name, int score) {
    std::osyncstream(std::cout) << "Appending to page " << page << " : " << name << " scored " << score << ".\n";
}

void useRange_for_each_n()
{
	std::vector final_ranking = get_rankings();
	std::ranges::sort(final_ranking, std::greater<>(), &Player::score);

	std::for_each_n(std::execution::par_unseq,
		final_ranking.begin(),
		std::min(MAIN_SEATS, final_ranking.size()),
		send_invitation_to_main_tournament); // 并行向前几位发送邀请

	// 每页显示PAGE_SIZE个人
	auto it = final_ranking.begin();
	uint32_t page = 0;
	while (it != final_ranking.end())
	{
		size_t cnt = std::min(PAGE_SIZE, size_t(final_ranking.end() - it));
		std::for_each_n(it, cnt, [page](const Player& p)
		{
			store_final_score(page, p.display_name, p.score);
		});
		page++;
		it += cnt;
	}
}

int main()
{
	// useRange_for_each();

	useRange_for_each_n();
}