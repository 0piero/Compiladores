#include <time.h>
#include "libs.h"
#include <math.h>

int main(int argc, char** argv){
	int i;
	time_t t;
	srand((unsigned) time(&t));

	Graph_adj* graph = alloc_graph_adj();

	Vertex* vtx0 = alloc_vtx();
	Vertex* vtx6 = alloc_vtx();
	Vertex* vtx7 = alloc_vtx();
	Vertex* vtx8 = alloc_vtx();
	Vertex* vtx9 = alloc_vtx();
	Vertex* vtx10 = alloc_vtx();
	Vertex* vtx11 = alloc_vtx();
	Vertex* vtx12 = alloc_vtx();
	Vertex* vtx13 = alloc_vtx();
	Vertex* vtx14 = alloc_vtx();
	Vertex* vtx15 = alloc_vtx();
	Vertex* vtx16 = alloc_vtx();
	Vertex* vtx17 = alloc_vtx();
	Vertex* vtx18 = alloc_vtx();
	Vertex* vtx19 = alloc_vtx();
	Vertex* vtx20 = alloc_vtx();
	Vertex* vtx21 = alloc_vtx();
	Vertex* vtx22 = alloc_vtx();
	Vertex* vtx23 = alloc_vtx();
	Vertex* vtx24 = alloc_vtx();

	graph_adj_insert_vtx(graph, vtx0);
	graph_adj_insert_vtx(graph, vtx6);
	graph_adj_insert_vtx(graph, vtx7);
	graph_adj_insert_vtx(graph, vtx8);
	graph_adj_insert_vtx(graph, vtx9);
	graph_adj_insert_vtx(graph, vtx10);
	graph_adj_insert_vtx(graph, vtx11);
	graph_adj_insert_vtx(graph, vtx12);
	graph_adj_insert_vtx(graph, vtx13);
	graph_adj_insert_vtx(graph, vtx14);
	graph_adj_insert_vtx(graph, vtx15);
	graph_adj_insert_vtx(graph, vtx16);
	graph_adj_insert_vtx(graph, vtx17);
	graph_adj_insert_vtx(graph, vtx18);
	graph_adj_insert_vtx(graph, vtx19);
	graph_adj_insert_vtx(graph, vtx20);
	graph_adj_insert_vtx(graph, vtx21);
	graph_adj_insert_vtx(graph, vtx22);
	graph_adj_insert_vtx(graph, vtx23);
	graph_adj_insert_vtx(graph, vtx24);

	/* q_0 */
	graph_adj_make_edge(graph, vtx0, vtx6);
	graph_adj_make_edge(graph, vtx0, vtx7);
	graph_adj_make_edge(graph, vtx0, vtx11);
	graph_adj_make_edge(graph, vtx0, vtx15);
	graph_adj_make_edge(graph, vtx0, vtx17);
	graph_adj_make_edge(graph, vtx0, vtx22);

	/* q_6 */
	graph_adj_make_edge(graph, vtx6, vtx24);

	/* q_7 */
	graph_adj_make_edge(graph, vtx7, vtx8); 
	graph_adj_make_edge(graph, vtx7, vtx14);
	graph_adj_make_edge(graph, vtx7, vtx6);
	graph_adj_make_edge(graph, vtx7, vtx24);

	/* q_8 */
	graph_adj_make_edge(graph, vtx8, vtx9); 
	graph_adj_make_edge(graph, vtx8, vtx10); 
	graph_adj_make_edge(graph, vtx8, vtx6); 
	graph_adj_make_edge(graph, vtx8, vtx24); 

	/* q_9 */
	graph_adj_make_edge(graph, vtx9, vtx10); 
	graph_adj_make_edge(graph, vtx9, vtx6); 
	graph_adj_make_edge(graph, vtx9, vtx24); 

	/* q_10 */
	graph_adj_make_edge(graph, vtx10, vtx24); 
	graph_adj_make_edge(graph, vtx10, vtx6);
	

	/* q_11 */
	graph_adj_make_edge(graph, vtx11, vtx12);
	graph_adj_make_edge(graph, vtx11, vtx13);
	graph_adj_make_edge(graph, vtx11, vtx18);
	graph_adj_make_edge(graph, vtx11, vtx8);
	graph_adj_make_edge(graph, vtx11, vtx6);
	graph_adj_make_edge(graph, vtx11, vtx24);

	/* q_12 */
	graph_adj_make_edge(graph, vtx12, vtx24);
	graph_adj_make_edge(graph, vtx12, vtx6);

	/* q_13 */
	graph_adj_make_edge(graph, vtx13, vtx24);
	graph_adj_make_edge(graph, vtx13, vtx14);
	graph_adj_make_edge(graph, vtx13, vtx6);

	/* q_14 */
	graph_adj_make_edge(graph, vtx14, vtx24);
	graph_adj_make_edge(graph, vtx14, vtx20);
	graph_adj_make_edge(graph, vtx14, vtx6);

	/* q_15 */
	graph_adj_make_edge(graph, vtx15, vtx16);
	graph_adj_make_edge(graph, vtx15, vtx6);
	graph_adj_make_edge(graph, vtx15, vtx24);

	/* q_16 */
	graph_adj_make_edge(graph, vtx16, vtx11);
	graph_adj_make_edge(graph, vtx16, vtx6);
	graph_adj_make_edge(graph, vtx16, vtx24);

	/* q_17 */
	graph_adj_make_edge(graph, vtx17, vtx7);
	graph_adj_make_edge(graph, vtx17, vtx6);
	graph_adj_make_edge(graph, vtx17, vtx24);

	/* q_18 */
	graph_adj_make_edge(graph, vtx18, vtx24);
	graph_adj_make_edge(graph, vtx18, vtx6);

	/* q_19 */
	graph_adj_make_edge(graph, vtx19, vtx24); 
	graph_adj_make_edge(graph, vtx19, vtx6);

	/* q_20 */
	graph_adj_make_edge(graph, vtx20, vtx21);
	graph_adj_make_edge(graph, vtx20, vtx6);
	graph_adj_make_edge(graph, vtx20, vtx24);

	/* q_21 */
	graph_adj_make_edge(graph, vtx21, vtx19);
	graph_adj_make_edge(graph, vtx21, vtx6); 
	graph_adj_make_edge(graph, vtx21, vtx24);

	/* q_22 */
	graph_adj_make_edge(graph, vtx22, vtx23);
	graph_adj_make_edge(graph, vtx22, vtx6);
	graph_adj_make_edge(graph, vtx22, vtx24);

	/* q_23 */
	graph_adj_make_edge(graph, vtx23, vtx11);
	graph_adj_make_edge(graph, vtx23, vtx6);
	graph_adj_make_edge(graph, vtx23, vtx24);

	List* arg = list_alloc();
	dfs(graph, (void*) arg);
	Node* hdy = ((List*) arg)->head;
	int max_k=0;

	while(hdy){
		ptr_array* code_data = (ptr_array*) hdy->item; 
		int arr_siz = code_data->size;
		int* arr = (int*) code_data->arr;
		int k = 0;
		for (int i=0;i<arr_siz;i++){
			k+=(int) pow(6, i) * arr[i];
			//printf("%d", arr[i]);
		}
		if (k>max_k){max_k = k;}
		//printf("\n");
		//printf("%d", k);
		//printf("\n");
		//printf("max_k: %d", max_k);
		//printf("\n");
		hdy = hdy->next; 
	}
	long int primes[8] = {7560193, 5422283, 9453859, 3778759, 5664707, 2929867, 8053187, 8854061};
	i = 0;
	int s_sqr = 0;
	int m = ((List*) arg)->s_list;
	//List* list_coll = list_alloc();
	typedef struct collis{
		long int* keys;
		int num_keys;
	} collis;
	collis array_collis[m];
	for(int j=0;j<m;j++){
		array_collis[j].keys = (long int*) malloc(sizeof(long int));
		array_collis[j].num_keys = 0;
	}
	int tbl[m];
	do{
		for (int j=0;j<m;j++){
			tbl[j] = 0;
		}
		int a = (rand() % (primes[i]-1)) + 1;
		int b = rand() % primes[i];
		Node* hdy = ((List*) arg)->head;
		while(hdy){
			ptr_array* code_data = (ptr_array*) hdy->item; 
			int arr_siz = code_data->size;
			int* arr = (int*) code_data->arr;
			int k = 0;
			for (int l=0;l<arr_siz;l++){
				k+=(int) pow(6, l) * arr[l];
			}
			int h = (((long int) a*k + b) % (long int) primes[i]) % m;
			tbl[h] += 1;
			array_collis[h].keys = (long int*) realloc(array_collis[h].keys, (array_collis[h].num_keys + 1) * sizeof(long int));
			(array_collis[h].keys)[array_collis[h].num_keys] = k;
			array_collis[h].num_keys += 1;

			hdy = hdy->next; 
		}
		s_sqr = 0;
		for (int j=0;j<m;j++){
			s_sqr += (int) pow(tbl[j], 2);
		}
		printf("n_j^2: %d \n", s_sqr);
		printf("4n: %d \n", 4*m);	
		i++;
	} while(s_sqr>4*m);

	printf("\n");
	printf("PASS %d\n", i - 1);
	
	for (i=0;i<m;i++){
		if (tbl[i] > 1){
			int colls;
			int p_idx;
			printf("entrada[%d]: <colisões: %d>\n", i, tbl[i]);
			do{
				colls = 0;
				int a = (rand() % (primes[p_idx]-1)) + 1;
				int b = rand() % primes[p_idx];
				p_idx = ((int)rand()) % 8;
				int tbl2[(int) pow(array_collis[i].num_keys, 2)];
				for (int j=0 ; j < pow(array_collis[i].num_keys, 2) ; j++){
					tbl2[j] = 0;
				}
				for (int j=0 ; j<array_collis[i].num_keys ; j++){
					long int k = (array_collis[i].keys)[j];
					int h = (((long int) a*k + b) % (long int) primes[p_idx]) % ((long int) pow(array_collis[i].num_keys, 2));
					printf("h: %d\n", h);
					tbl2[h] += 1;
				}
				for (int j=0 ; j < pow(array_collis[i].num_keys, 2) ; j++){
					if (tbl2[j] > 1){
						colls += 1;
					}
				}
				printf("%d: <colls %d>\n", i, colls);


			}while(colls > 0);

		}
	}

	return 0;

}
