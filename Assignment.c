#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product {
	char ProId[20];
	char ProName[30];
	float Price;
	int Quantity;
	int CatId;
} Pro;

typedef struct Category {
	int CatId;
	char CatName[20];
} Cat;

void menu() {
	printf("1. Nhap thong tin cho n san pham\n");
	printf("2. In danh sach cac san pham\n");
	printf("3. Sap xep va in danh sach san pham theo gia giam dan\n");
	printf("4. Sua doi thong tin san pham theo ma san pham\n");
	printf("5. Tim kiem va in danh sach san pham theo ten danh muc\n");
	printf("6. Thoat\n");
}

void readFile(Pro a[], int *na, Cat b[], int *nb) {
	FILE *fp;
	if ((fp = fopen("Product.dat", "r")) == NULL) {
		printf("ERROR WITH FILE!");
		return;
	}
	int i = 0;
	while (fscanf(fp, "%s | %[^|] | %f | %d | %d", 
			a[i].ProId, a[i].ProName, &a[i].Price, &a[i].Quantity, &a[i].CatId) != EOF) {
		i++;
	}
	*na = i;
	
	if ((fp = fopen("Category.dat", "r")) == NULL) {
		printf("ERROR WITH FILE!");
		return;
	}
	i = 0;
	while (fscanf(fp, "%d | %[^\n]", 
			&b[i].CatId, b[i].CatName) != EOF) {
		i++;
	}
	*nb = i;
	fclose(fp);
}

void input(Pro a[], int *na, Cat b[], int *nb) {
	printf("Enter number of products you want to add: ");
	int n; 
	scanf("%d", &n);
	while (n-- > 0) {
		printf("Enter product %d\n", *na+1);
		
		fflush(stdin);
		printf("Enter product id: ");
		scanf("%s%*c", a[*na].ProId);
		
		printf("Enter product name: ");
		scanf("%[^\n]%*c", a[*na].ProName);
		
		printf("Enter product price: ");
		scanf("%f", &a[*na].Price);
		
		printf("Enter product quantity: ");
		scanf("%d", &a[*na].Quantity);
		
		printf("Enter CatId of product: ");
		scanf("%d", &a[*na].CatId);
		
		(*na)++;
		printf("\n");
	}
}

void displayProduct(Pro a[], int na) {
	int i;
	for (i = 0; i < na; i++) {
		printf("%s\t%s\t\t%.2f\t\t%d\t%d\n", a[i].ProId, a[i].ProName, a[i].Price, a[i].Quantity, a[i].CatId);
	}
}

void sortByPrice(Pro a[], int na) {
	int i, j;
	for (i = 0; i < na - 1; i++) {
		for (j = 0; j < na - 1 - i; j++) {
			if (a[j].Price < a[j+1].Price) {
				Pro temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
	displayProduct(a, na);
}

void updateProduct(Pro a[], int na) {
	printf("Enter product id to update: ");
	char id[20];
	fflush(stdin);
	scanf("%[^\n]%*c", id);
	
	int i, found = 0;
	for (i = 0; i < na; i++) {
		if (strcmp(a[i].ProId, id) == 0) {
			found = 1;
			printf("Enter new name: ");
			scanf("%[^\n]%*c", a[i].ProName);
			
			printf("Enter new price: ");
			scanf("%f", &a[i].Price);
			
			printf("Enter new quantity: ");
			scanf("%d", &a[i].Quantity);
			
			printf("Enter new category id: ");
			scanf("%d", &a[i].CatId);
			
			printf("Update successful");
			break;		
		}
	}
	
	if (found == 0) {
		printf("Product with id %s not exist", id);
	}
}

void writeFile(Pro a[], int na, Cat b[], int nb) {
	FILE *fp;
	if ((fp = fopen("Product.dat", "w")) == NULL) {
		printf("ERROR WITH FILE!");
		return;
	}
	
	int i;
	for (i = 0; i < na; i++) {
		fprintf(fp, "%s | %s | %.2f | %d | %d\n",
			a[i].ProId, a[i].ProName, a[i].Price, a[i].Quantity, a[i].CatId);
	}
	
	if ((fp = fopen("Category.dat", "w")) == NULL) {
		printf("ERROR WITH FILE!");
		return;
	}
	
	for (i = 0; i < nb; i++) {
		fprintf(fp, "%d | %s\n",
			b[i].CatId, b[i].CatName);
	}
	fclose(fp);
}

int main() {
	Pro a[100];
	Cat b[100];
	int na = 0, nb = 0, choice;
	readFile(a, &na, b, &nb);
	do {
		menu();
		printf("Choose: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				input(a, &na, b, &nb);
				break;
			case 2:
				displayProduct(a, na);
				break;
			case 3:
				sortByPrice(a, na);
				break;
			case 4:
				updateProduct(a, na);
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				printf("Invalid choice!!");
				break;
		}
		printf("\n");
		system("pause");
		system("cls");
	} while (choice != 6);
	
	writeFile(a, na, b, nb);
}
