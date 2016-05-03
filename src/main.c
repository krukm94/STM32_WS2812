/* second project 
	Michal K
*/


/*=============includes============== */
#include "init.h"


/*=============variables==============*/

/*=============macros=================*/

/*=============functions==============*/

/*===============main=================*/

int main(void) {
	int i,k;
	init();
	
	while(1) {
		
		HAL_Delay(1);
		k = 0;
		for(i = 0 ; i < 30 ; i++){
			dioda(255,0,0);
			k++;
		}
		
	} //while(1)
		
}
