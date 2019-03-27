#include "include_files.h"
#include "solver_file.h"

int main( void ) {

system("cp /dev/null output_data_point_funct_2.txt");//чистим файл перед прочитыванием
system("cp /dev/null output_data_animate_2.txt");//чистим файл перед прочитыванием
system("cp /dev/null vars.txt");

std::fstream outdata1("output_data_point_funct_2.txt");
std::fstream outdata2("output_data_animate_2.txt");
std::fstream varstxt("vars.txt");

main_solver(outdata1,outdata2,varstxt);

if ( !system("./plot_command.gnu ") )
     std::cout << "в этой папке создан файлы с графиками X.eps , animate.gif и graph_moment.gif" <<std::endl;

outdata1.close();
outdata2.close();
varstxt.close();

}
