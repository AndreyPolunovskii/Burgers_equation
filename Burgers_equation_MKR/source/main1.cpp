#include "solver_file.h"



int main()
{
    
int prec = (int) (col_sign / log10(2) );


    
    
system("cp /dev/null output_data_point_funct_2.txt");//чистим файл перед прочитыванием
system("cp /dev/null output_data_animate_2.txt");//чистим файл перед прочитыванием
system("cp /dev/null vars.txt");

fstream outdata1("output_data_point_funct_2.txt");
fstream outdata2("output_data_animate_2.txt");
fstream varstxt("vars.txt");

cout << endl;
cout << "Длина отрезка по времени = " << T << endl;
cout << "Длина отрезка по пространству = " << ( col_space_point - 1) * h << endl;

main_solver((int)time_steps,outdata1,outdata2,varstxt);



system("./plot_command.gnu ");
cout << "в этой папке создан файлы с графиками X.eps , animate.gif и graph_moment.gif" <<endl;

outdata1.close();
outdata2.close();
varstxt.close();


return 0;
}
