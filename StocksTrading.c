/*
 * tradingstocks.c
 * Author: St George Pennant
 * Ticker: CARG
 *
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_PRICES_SIZE 30

void test();
void banner();
void readPrices(char* fileName, int pricesCapacity, double* pPrices, int* pricesSize);
double getMinPrice(double* pPrices, int size);
double getMaxPrice(double* pPrices, int size);
void profitableTrades(double* pPrices, int pricesSize, double* pProfits, int* pProfitsSize);
void save(char* filename, double* pProfits, int profitsSize);
void print(double* pProfits, int profitsSize);

void banner()
{
	printf("======================================\n");
	printf("Welcome To The Stock Profit Calculator\n");
	printf("======================================\n");
}

void readPrices(char* fileName, int pricesCapacity, double* pPrices, int* pricesSize) {
	FILE* pFile = 0;
	double price;
	//i=0;
	pFile = fopen("prices.txt", "r");

	if (pFile == NULL) {
		printf("Error: File was not opened\n");
	}
	while (fscanf(pFile, "%lf", &price) != EOF) {
		pPrices[*pricesSize] = price;
		(*pricesSize)++;
	}

	if (pFile) fclose(pFile);
}

double getMinPrice(double* pPrices, int size) {
	int i = 0;
	double minPrice = pPrices[i];

	for (i = 1; i < size; i++) {
		if (minPrice > pPrices[i]) {
			minPrice = pPrices[i];
		}
	}

	return minPrice;
}

double getMaxPrice(double* pPrices, int size) {
	int i = 0;
	double maxPrice = pPrices[i];

	for (i = 1; i < size; i++) {
		if (maxPrice < pPrices[i]) {
			maxPrice = pPrices[i];
		}
	}

	return maxPrice;

}
void profitableTrades(double* pPrices, int pricesSize, double* pProfits, int* pProfitsSize) {
	int i;
	double currentSellMaxPrice;
	double currentBuyPrice;
	double currentMaxProfit;
	*pProfitsSize = 0;

	for (i = pricesSize - 1; i >= 0; i--) {
		currentBuyPrice = pPrices[i];
		currentSellMaxPrice = getMaxPrice(pPrices, i);
		currentMaxProfit = currentSellMaxPrice - currentBuyPrice;
		if (currentMaxProfit > 0) {
			pProfits[*pProfitsSize] = currentMaxProfit;
			(*pProfitsSize)++;
		}
	}
}
void save(char* filename, double* pProfits, int profitsSize) {
	int i;
	FILE* pFile = 0;
	pFile = fopen("profits.txt", "w");
	if (pFile)
	{
		for (i = 0; i < profitsSize; i++) {
			fprintf(pFile, "Profits[%d]=$%.2lf\n", i, pProfits[i]);
		}

	}
	else {
		printf("Error: File was not opened\n");
		exit(0);
	}

	if (pFile) fclose(pFile);

}

void print(double* pProfits, int profitsSize) {
	int i = 0;
	double maxProfit = pProfits[i];

	for (i = 0; i < profitsSize; i++) {
		printf("Profits[%d]=$%.2lf\n\n", i, pProfits[i]);
	}


	for (i = 1; i < profitsSize; i++) {
		if (maxProfit < pProfits[i]) {
			maxProfit = pProfits[i];
		}
	}
	printf("********************\n");
	printf("*MAX PROFIT =$ %.2lf*\n", maxProfit);
	printf("********************\n");
}

void test() {
	char* fileName = "prices.txt";
	double prices[MAX_PRICES_SIZE];
	double profits[MAX_PRICES_SIZE];
	int pricesSize = 0;
	int profitsSize = 0;
	int i;
	double minPrice;
	double maxPrice;



	banner();
	readPrices(fileName, MAX_PRICES_SIZE, prices, &pricesSize);
	for (i = 0; i < pricesSize; i++) {
		printf("Prices[%d]=$%.2lf\n\n", i, prices[i]);
	}

	minPrice = getMinPrice(prices, pricesSize);
	printf("==========================\n");
	printf("The Minimum Price is %.2lf\n", minPrice);
	maxPrice = getMaxPrice(prices, pricesSize);
	printf("The Maximum Price is %.2lf\n", maxPrice);
	printf("==========================\n\n");
	profitableTrades(prices, pricesSize, profits, &profitsSize);
	//for(i=0; i<profitsSize; i++) {
		//printf("profits[%d]=%.2lf\n",i,profits[i]);
	//}

	//printf("The minimum price is %.2lf\n",minPrice);
	//printf("The maximum price is %.2lf\n",maxPrice);

	save("profits.txt", profits, profitsSize);
	print(profits, profitsSize);

}


int main()
{
	test();
	return 0;
}
