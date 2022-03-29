#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
struct employee {
	char name[21];
	char job[16];
	int salary;
};
void header() {
	std::cout << "Employee             |          Job    | Salary \n"
			"---------------------+-----------------+---------\n";
}
void row(const employee &empl) {
	std::cout << std::setw(20) << std::left << empl.name << " | "
			<< std::setw(15) << std::left << empl.job << " | " << std::setw(7)
			<< std::right << empl.salary << std::endl;
}
void read_file(const char *filename, std::vector<employee> &list) {
	list.clear();
	std::ifstream data_file { filename, std::ios::binary };
	if (not data_file)
		return;
	employee empl;
	while (data_file.read(reinterpret_cast<char*>(&empl), sizeof(empl)))
		list.push_back(empl);
	data_file.close();
}
void write_file(const char *filename, std::vector<employee> &list) {
	std::ofstream data_file { filename, std::ios::binary };
		for (auto &&e : list){
			data_file.write(reinterpret_cast<char*>(&e), sizeof(e));
		}
		data_file.close();
}
void input_employee(std::vector<employee> &list) {

	employee empl;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "���:";
	std::cin.getline(empl.name, sizeof(empl.name));
	std::cout << "���������:";
	std::cin.getline(empl.job, sizeof(empl.job));

	std::cout << "��������:";
	std::cin >> empl.salary;
	list.push_back(empl);
}
void delete_empl(){

}
void change_empl(){

}
int main() {
	std::vector<employee> empl_roster;

	read_file("empl_roster.db", empl_roster);

	int choice;
	do {
		menu: std::cout << "   �������� ��� �������:\n"
				"   ---------------------\n"
				" 1. ������� ������\n"
				" 2. �������� ����������\n"
				" 3. �������� ������\n"
				" 4. ������� ������\n"

				"\n"
				" 0. �����\n"
				"---> ";

		if (not (std::cin >> choice)) {
			if (std::cin.eof()) {
				std::cerr << "������ �����-������" << std::endl;
				return 1;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			goto menu;
		}

		switch (choice) {
		case 0:
			std::cout << "�� ��������!" << std::endl;
			break;
		case 1:
			header();
			for (auto &&e : empl_roster)
				row(e);
			break;
		case 2:
			input_employee(empl_roster);
			break;
		default:
			std::cout << "��� ������ ��������!" << std::endl;
		}

	} while (choice != 0);

	write_file("empl_roster.db", empl_roster);

	return 0;
}
