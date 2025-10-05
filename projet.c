// RANIA BLIBEK 21215298 
//AMINE IDRES 21322043
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Structure pour représenter un nombre complexe
typedef struct Complex {
    double real;      // Partie réelle
    double imaginary; // Partie imaginaire
} Complex;
Complex add(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imaginary = a.imaginary + b.imaginary;
    return result;
}

// Function to subtract two complex numbers
Complex subtract(Complex a, Complex b) {
    Complex result;
    result.real = a.real - b.real;
    result.imaginary = a.imaginary - b.imaginary;
    return result;
}

// Function to multiply two complex numbers


// Function to divide two complex numbers
Complex divide(Complex a, Complex b) {
    Complex result;
    double denominator = b.real * b.real + b.imaginary * b.imaginary;

    if (denominator != 0) {
        result.real = (a.real * b.real + a.imaginary * b.imaginary) / denominator;
        result.imaginary = (a.imaginary * b.real - a.real * b.imaginary) / denominator;
    } else {
        printf("Error: Division by zero.\n");
        // You might want to handle division by zero differently based on your requirements.
    }

    return result;
}

// Function to calculate the magnitude of a complex number
double magnitude(Complex num) {
    return sqrt(num.real * num.real + num.imaginary * num.imaginary);
}

// Fonction qui permet de faire une copie d'un vecteur de forme Complex
Complex* copyComplexArray(Complex* source, int n) {
    Complex* copie = (Complex*)malloc(n * sizeof(Complex));
    if (copie == NULL) {
        // Gestion de l'échec de l'allocation mémoire
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        copie[i] = source[i];
    }
    return copie;
}

// Calcule l'FFT
#define M_PI 3.14159265358979323846

// Fonction pour calculer l'FFT (Fast Fourier Transform)
void fft(Complex *L, int n, int sign) {
    if (n == 1) {
        return;
    }

    Complex w_n;
    w_n.real = cos(sign * 2 * M_PI / n);
    w_n.imaginary = sin(sign * 2 * M_PI / n);

    Complex w = {1.0, 0.0};
    Complex *F_even = (Complex *)malloc((n / 2) * sizeof(Complex));
    Complex *F_odd = (Complex *)malloc((n / 2) * sizeof(Complex));

    for (int i = 0; i < n / 2; ++i) {
        F_even[i] = L[2 * i];
        F_odd[i] = L[2 * i + 1];
    }

    fft(F_even, n / 2, sign);
    fft(F_odd, n / 2, sign);

    for (int k = 0; k < n / 2; ++k) {
        Complex t = {
            w.real * F_odd[k].real - w.imaginary * F_odd[k].imaginary,
            w.real * F_odd[k].imaginary + w.imaginary * F_odd[k].real
        };

        L[k] = (Complex) {
            F_even[k].real + t.real,
            F_even[k].imaginary + t.imaginary
        };

        L[k + n / 2] = (Complex) {
            F_even[k].real - t.real,
            F_even[k].imaginary - t.imaginary
        };

        w = (Complex) {
            w.real * w_n.real - w.imaginary * w_n.imaginary,
            w.real * w_n.imaginary + w.imaginary * w_n.real
        };
    }

    free(F_even);
    free(F_odd);
}

void ifft(Complex* vec, int n) {
    fft(vec, n, 1);

    for (int i = 0; i < n; ++i) {
        vec[i].real /= n;
        vec[i].imaginary /= n;
    }
}




Complex mul(Complex a, Complex b) {
    Complex result;
    result.real = a.real * b.real - a.imaginary * b.imaginary;
    result.imaginary = a.real * b.imaginary + a.imaginary * b.real;
    return result;
}

int* multiplication_naive(int* a, int* b, int n, int m) {
    // Multiply polynomials a and b of degree n and m, respectively,
    // and return the resulting polynomial of degree n+m.
    int* c = calloc(n + m + 1, sizeof(int));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    return c;
}

int *multiply(int *P, int *Q, int len_P, int len_Q) {
    int n = 1;
    while (n <= len_P + len_Q) {
        n <<= 1;
    }

    Complex *P_complex = (Complex *)malloc(n * sizeof(Complex));
    Complex *Q_complex = (Complex *)malloc(n * sizeof(Complex));

    // Initialiser les parties réelles des polynômes avec les coefficients et les parties imaginaires avec 0
    for (int i = 0; i < len_P; ++i) {
        P_complex[i] = (Complex){(double)P[i], 0.0};
    }

    for (int i = len_P; i < n; ++i) {
        P_complex[i] = (Complex){0.0, 0.0};
    }

    for (int i = 0; i < len_Q; ++i) {
        Q_complex[i] = (Complex){(double)Q[i], 0.0};
    }

    for (int i = len_Q; i < n; ++i) {
        Q_complex[i] = (Complex){0.0, 0.0};
    }

    // Appliquer FFT aux polynômes
    fft(P_complex, n, 1);
    fft(Q_complex, n, 1);

    // Produit des polynômes dans le domaine de la fréquence
    for (int i = 0; i < n; ++i) {
        Complex product = {
            P_complex[i].real * Q_complex[i].real - P_complex[i].imaginary * Q_complex[i].imaginary,
            P_complex[i].real * Q_complex[i].imaginary + P_complex[i].imaginary * Q_complex[i].real
        };

        P_complex[i] = product;
    }

    // Appliquer l'IFFT pour obtenir le résultat dans le domaine des coefficients
    fft(P_complex, n, -1);

    // Récupérer les parties réelles, diviser par n et arrondir aux entiers
    int *result = (int *)malloc((len_P + len_Q + 1) * sizeof(int));
    for (int i = 0; i <= len_P + len_Q; ++i) {
        result[i] = (int)round(P_complex[i].real / n);
    }

    free(P_complex);
    free(Q_complex);

    return result;
}



int* polynome_aleatoire(int n) {
    // Allouer de la mémoire pour le polynôme
    int* poly = (int*)malloc((n + 1) * sizeof(int));

    // Générer des coefficients aléatoires pour le polynôme
    for (int i = 0; i <= n; ++i) {
        poly[i] = rand() % 100;  // Générer un nombre aléatoire entre 0 et 99
    }

    return poly;
}

void generate_plot_script_naive() {
    FILE* script_file = fopen("plot_script_naive.gp", "w");
    if (script_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de script naïf");
        exit(EXIT_FAILURE);
    }

    fprintf(script_file, "set title 'Comparaison des temps exécution (Naïf)'\n");
    fprintf(script_file, "set xlabel 'Taille du polynôme'\n");
    fprintf(script_file, "set ylabel 'Temps (secondes)'\n");
    fprintf(script_file, "plot 'times_naive.txt' using 1 with lines title 'Naive' lt rgb 'blue'\n");

    fclose(script_file);
}

void generate_plot_script_fft() {
    FILE* script_file = fopen("plot_script_fft.gp", "w");
    if (script_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de script FFT");
        exit(EXIT_FAILURE);
    }

    fprintf(script_file, "set title 'Comparaison des temps exécution (FFT)'\n");
    fprintf(script_file, "set xlabel 'Taille du polynôme'\n");
    fprintf(script_file, "set ylabel 'Temps (secondes)'\n");
    fprintf(script_file, "plot 'times_fft.txt' using 1 with lines title 'FFT' lt rgb 'red'\n");

    fclose(script_file);
}

void time_affichage(int max_n, int m) {
    FILE* file_naive = fopen("times_naive.txt", "w");
    FILE* file_fft = fopen("times_fft.txt", "w");

    for (int n = 1; n <= max_n; ++n) {
        int* aa = polynome_aleatoire(n);
        int* bb = polynome_aleatoire(m);

        clock_t start = clock();
        int* c_naive = multiplication_naive(aa, bb, n, m);
        clock_t end = clock();
        double time_taken_naive = ((double)end - start) / CLOCKS_PER_SEC;
        printf("multiplication_naive avec n=%d et m=%d a pris %f secondes pour s'exécuter.\n", n, m, time_taken_naive);
        fprintf(file_naive, "%f\n", time_taken_naive);
        free(c_naive);

        start = clock();
        int* c_fft = multiply(aa, bb, n, m);
        end = clock();
        double time_taken_fft = ((double)end - start) / CLOCKS_PER_SEC;
        printf("multiplication_FFT avec n=%d et m=%d a pris %f secondes pour s'exécuter.\n\n\n", n, m, time_taken_fft);
        fprintf(file_fft, "%f\n", time_taken_fft);
        free(c_fft);

        free(aa);
        free(bb);
    }

    fclose(file_naive);
    fclose(file_fft);

    // Générer les scripts Gnuplot
    generate_plot_script_naive();
    generate_plot_script_fft();

    // Afficher les graphiques
    system("gnuplot -p plot_script_naive.gp");
    getchar(); // Attendre une entrée de l'utilisateur
    system("gnuplot -p plot_script_fft.gp");
}
void printPolynomial(int *poly, int degree) {
    for (int i = degree; i >= 0; --i) {
        printf("%dx^%d ", poly[i], i);
        if (i > 0) {
            printf("+ ");
        }
    }
    printf("\n");
}

void displayMenu() {
    printf("1. Multiplication naive \n");
    printf("2. multiplication avec FFT \n");
    printf("3. Test et temps d'execution\n");
    printf("4.exit\n");
}

int main() {
    int choice;
    int start ;
    int end;
    int len_P, len_Q;
    int *P_naive, *Q_naive;
    int *P_fft, *Q_fft; 
    int *result_fft,*result_naive; 

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                

    printf("Entrez le degré du polynôme P : ");
    scanf("%d", &len_P);

    int *P_naive = (int *)malloc((len_P + 1) * sizeof(int));
    printf("Saisissez les coefficients du polynôme P, du terme constant au terme de plus haut degré :\n");
    for (int i = 0; i <= len_P; ++i) {
        scanf("%d", &P_naive[i]);
    }

    printf("Entrez le degré du polynôme Q : ");
    scanf("%d", &len_Q);

    int *Q_naive = (int *)malloc((len_Q + 1) * sizeof(int));
    printf("Saisissez les coefficients du polynôme Q, du terme constant au terme de plus haut degré :\n");
    for (int i = 0; i <= len_Q; ++i) {
        scanf("%d", &Q_naive[i]);
    }
    start = clock();
    int *result_naive = multiplication_naive(P_naive, Q_naive, len_P + 1, len_Q + 1);
    end = clock();
    

    // Affichage des tableaux de coefficients des polynômes P, Q et du résultat
    printf("Polynôme P : ");
    printPolynomial(P_naive, len_P);
    printf("Polynôme Q : ");
    printPolynomial(Q_naive, len_Q);
    printf("Résultat de la multiplication : ");
    printPolynomial(result_naive, len_P + len_Q);
    double time_taken_naive = ((double)end - start) / CLOCKS_PER_SEC;
    printf("La multiplication naive  a pris %f secondes.\n", time_taken_naive);
    

    

    // Libérer la mémoire
    free(P_naive);
    free(Q_naive);
    free(result_naive);

                break;

            case 2:
                printf("Entrez le degré du polynôme P : ");
    scanf("%d", &len_P);

    int *P_fft = (int *)malloc((len_P + 1) * sizeof(int));
    printf("Saisissez les coefficients du polynôme P, du terme constant au terme de plus haut degré :\n");
    for (int i = 0; i <= len_P; ++i) {
        scanf("%d", &P_fft[i]);
    }

    printf("Entrez le degré du polynôme Q : ");
    scanf("%d", &len_Q);

    int *Q_fft = (int *)malloc((len_Q + 1) * sizeof(int));
    printf("Saisissez les coefficients du polynôme Q, du terme constant au terme de plus haut degré :\n");
    for (int i = 0; i <= len_Q; ++i) {
        scanf("%d", &Q_fft[i]);
    }
    start = clock();
    int *result_fft = multiply(P_fft, Q_fft, len_P + 1, len_Q + 1);
    end = clock();
    

    // Affichage des tableaux de coefficients des polynômes P, Q et du résultat
    printf("Polynôme P : ");
    printPolynomial(P_fft, len_P);
    printf("Polynôme Q : ");
    printPolynomial(Q_fft, len_Q);
    printf("Résultat de la multiplication : ");
    printPolynomial(result_fft, len_P + len_Q);
    double time_taken_fft = ((double)end - start) / CLOCKS_PER_SEC;
    printf("La multiplication FFT a pris %f secondes.\n", time_taken_fft);
    

    

    // Libérer la mémoire
    free(P_fft);
    free(Q_fft);
    free(result_fft);
                break;

            case 3:
                time_affichage(1000, 1000);
                break;

            case 4:
                printf("\n\nAu revoir !\n\n");
                exit(EXIT_SUCCESS); // Quitte le programme proprement
                break;

            default:
                printf("Choix invalide. Veuillez choisir à nouveau.\n");
        }

    } while (choice != 4);

    return 0;
}
