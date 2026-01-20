🧠 Philosophers — README

Implementación del proyecto Philosophers del cursus 42.
Simulación del problema de los filósofos usando hilos y mutex, sin variables globales, sin data races y sin memory leaks.

📦 Compilación
make


Recompilar desde cero:

make re

▶️ Ejecución

Formato:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


Todos los tiempos están en milisegundos.

✅ Comandos de prueba recomendados
1️⃣ Caso básico (simulación estable)
./philo 5 800 200 200


Debe ejecutarse sin errores.
Puede durar indefinidamente si nadie muere.

2️⃣ Caso 1 filósofo
./philo 1 200 100 100


Resultado esperado:

toma un tenedor

muere tras ~200 ms

3️⃣ Caso imposible (muerte garantizada)
./philo 2 101 100 100


Resultado esperado:

uno de los filósofos muere

la simulación se detiene

4️⃣ Parada por número de comidas (argumento obligatorio)
./philo 5 800 200 200 3


Resultado esperado:

ningún filósofo muere

la simulación se detiene automáticamente

no se imprime ningún mensaje especial al finalizar

5️⃣ Test de estrés
./philo 50 800 200 200 2


Resultado esperado:

no deadlock

termina correctamente

sin muertes

❌ Tests de errores de argumentos
./philo a 800 200 200
./philo 5 800 200
./philo 5 800 200 200 0


Resultado esperado:

mensaje de error

salida con código distinto de 0

sin crash

🧪 Valgrind
Test normal
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200 3


Resultado esperado:

All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors

Test con muerte
valgrind --leak-check=full --show-leak-kinds=all ./philo 2 101 100 100


También debe mostrar:

ERROR SUMMARY: 0 errors

✅ Reglas respetadas

Sin variables globales

Un hilo por filósofo

Un mutex por tenedor

Mutex para impresión

Mutex para estado compartido

Prevención de deadlock

Monitor independiente

Parada limpia de la simulación

Sin memory leaks

ℹ️ Notas

El tiempo de vida se mide desde que el filósofo empieza a comer, no desde que termina.

El argumento number_of_times_each_philosopher_must_eat forma parte de la parte obligatoria.

Al cumplirse el número de comidas, la simulación se detiene sin imprimir ningún mensaje adicional.
