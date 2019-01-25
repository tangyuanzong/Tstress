#include "Tstress.h"

int main(int argc, char *argv[]){
    
    Tstress stress;

    if(argc == 1){
       stress.Stress_usage();
       return 1;
    }
    stress.Stress_init();
    stress.Stress_opt(argc, argv);
    stress.Stress_http(argv[optind]);
    stress.Stress_start();
}
