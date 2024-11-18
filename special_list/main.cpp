#include "my_list.h"
#include <chrono>

using namespace std;

void log(string filename, string text) noexcept
{
	ofstream fout(filename, ios::app);
	auto now = chrono::system_clock::now();
	auto in_time_t = chrono::system_clock::to_time_t(now);
	tm buf;
	localtime_s(&buf, &in_time_t);
	fout << put_time(&buf, "%Y-%m-%d %H:%M:%S") << "; " << text << "\n";
}

int main()
{
	string log_txt = "log.txt";
	try
	{
		string input_txt = "WordsList.txt";
		string output_txt = "ResultPairs.txt";

		ifstream fin(input_txt);

		if (!fin.is_open()) {
			throw runtime_error("Ошибка: невозможно открыть файл " + input_txt);
		}

		MyList<string> list_of_words;
		string word;
		while (fin >> word)
		{
			if (fin.bad()) {
				throw runtime_error("Ошибка чтения из файла.");
			}
			list_of_words.push_front(word);
		}
		list_of_words.sort();
		MyList<string> map;
		Node<string>* head = list_of_words.first();
		while (head != list_of_words.end())
		{
			map.push_front(head->key, 1);
			head = head->next;
		}
		map.sort();
		map.print();
		map.write_file(output_txt);
	}
	catch (const std::exception& e)
	{
		cerr << "Исключение: " << e.what() << endl;
		log(log_txt, e.what());
		return 1;
	}
	log(log_txt, "Успешно");
	return 0;
}