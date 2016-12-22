#include<iostream>
#include <vector>

enum class Color { White, Wheatish, Black };
enum class Game { Cricket, Soccer, BasketBall};
enum class Hight { Small, Average, High };

class Human {
	public:
	std::string name;
	Color color;
	Game game;
	Hight hight ;
};


template <typename T> class FilterCriteria {
	public:
	virtual bool isMatched(T* item) = 0;
};

template <typename T> class IFilter {
	public:
	virtual std::vector<T*> filter(std::vector<T*> items, FilterCriteria<T>& criteria)=0;
};

class HumanFilter :public IFilter<Human> {
	typedef std::vector<Human*> Humans;
	public:
	Humans filter( Humans collections, FilterCriteria<Human>& criteria) override {
	Humans result;
		for (auto& item : collections) {
			if(criteria.isMatched(item)){
				result.push_back(item);	
			}
		}
		return result;
	}
};

class GameFilterCriteria :public FilterCriteria<Human> {
	public:
	explicit GameFilterCriteria(const Game game): m_game {game} {}
	bool isMatched(Human* h ) override {
		return h->game == m_game;
	}
	private:
	Game m_game;
};

class ColorimetryCriteria :public FilterCriteria<Human> {
	public:
	explicit ColorimetryCriteria(const Color color): m_color {color} {}
	bool isMatched(Human* h ) override {
		return h->color == m_color;
	}
	private:
	Color m_color;
};

int main() {
	Human asian{"Asian", Color::Wheatish, Game::Cricket, Hight::Average};
	Human european {"European", Color::White, Game::Soccer, Hight::High};
	Human african{ "African", Color::Black, Game::BasketBall, Hight::High};
	Human australian{ "Australia", Color::White, Game::Cricket, Hight::High};

	std::vector<Human*> human {&asian, &european, &african, &australian};
        	
	HumanFilter human_filter;

	std::cout<<std::endl<<"--------------------Filter by game-------------------------\n";
	GameFilterCriteria game(Game::Cricket);
	auto cricket_playing_country = human_filter.filter(human, game);
	for (auto & item : cricket_playing_country) {
		std::cout<< item->name << " is cricket playing country. " <<std::endl;
	}
	
	std::cout<<std::endl<<"--------------------Filter by color-------------------------\n";
	
	ColorimetryCriteria color(Color::White);
	auto white_color_human = human_filter.filter(human, color);
	for (auto & item : white_color_human) {
		std::cout<< item->name << " are white color human." <<std::endl;
	}
	return 1;
}
