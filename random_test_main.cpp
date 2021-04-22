#include <stdio.h>
#include <kiss.h>
#include <memory.h>
#include <malloc.h>



int main()
{
	int i, d, p, nline, num;
	double b, c;
	int r[10] = { 0,0,0,0,0,0,0,0,0,0 };
	double sum = 0.0, ave = 0.0;
	int niteration = 100;
	unsigned int u;


	struct kiss_state* vstate = (struct kiss_state*)malloc(sizeof(struct kiss_state));
	vstate->x = 123456789;
	vstate->y = 987654321;
	vstate->z = 43219876;
	vstate->c = 6543217;

	printf("\n x=%u, y=%u, z=%u, c=%u \n", vstate->x, vstate->y, vstate->z, vstate->c);

	printf("\n UINT_MAX=%lu, ULONG_MAX=%llu, ULLONG_MAX=%llu \n", UINT_MAX, ULONG_MAX, ULLONG_MAX);


	init_kiss(vstate);
	printf("\n %d outputs of kiss_get()%5\n", niteration);
	for (i = 0; i < 500; i++)
	{
		printf("%u ", kiss_get(vstate) % 5);
		if (i % 20 == 19) printf("\n");
	}

	init_kiss(vstate);
	printf("\n x=%u, y=%u, z=%u, c=%u \n", vstate->x, vstate->y, vstate->z, vstate->c);

	printf("\n %d outputs of kiss_get_double_better()\n", niteration);
	for (i = 0; i < niteration; i++)
	{
		b = kiss_get_double_better(vstate);
		printf("%f ", b);
		if (i % 20 == 19) printf("\n");
		if (b > 1.00)
		{
			printf("\n error \n");
			break;
		}

		d = round(b * 1000);
		p = d / 100;
		switch (p)
		{
		case 0:
			r[0] += 1;
			break;
		case 1:
			r[1] += 1;
			break;
		case 2:
			r[2] += 1;
			break;
		case 3:
			r[3] += 1;
			break;
		case 4:
			r[4] += 1;
			break;
		case 5:
			r[5] += 1;
			break;
		case 6:
			r[6] += 1;
			break;
		case 7:
			r[7] += 1;
			break;
		case 8:
			r[8] += 1;
			break;
		case 9:
			r[9] += 1;
			break;
		default:
			break;
		}
		sum += b;
	}

	ave = sum / niteration;

	printf("\n Histogram of random real number between 0 and 1: \n");
	for (i = 0; i < 10; i++)
	{
		if (i < 9)
			printf("Number between 0.%d and 0.%d : %d\n", i, i + 1, r[i]);
		else
			printf("Number between 0.%d and 1.0: %d\n", i, r[i]);
	}
	printf("\n Average is: %f\n", ave);

	free(vstate);
	return 0;
}



