Proyecto 2: Programación Orientada a Objetos en Kotlin
Este proyecto incluye cuatro programas desarrollados en Kotlin, aplicando conceptos de Programación Orientada a Objetos (POO).
Contenido

Cuenta BancariaSimula una cuenta bancaria con atributos de saldo y límite de retiro. Incluye validaciones para operaciones de retiro según reglas definidas.

ProductoRepresenta un producto con precio y porcentaje de descuento. Valida los valores ingresados y calcula el precio final con descuento aplicado.

FigurasImplementa clases para Cuadrado, Rectángulo y Círculo, con métodos para calcular área y perímetro de cada figura.

BibliotecaSistema básico de gestión de biblioteca con materiales (libros y revistas), usuarios y operaciones de préstamo y devolución.


Requisitos

Kotlin SDK instalado.
Git Bash (o una terminal compatible) para compilación y ejecución.

Instrucciones de Ejecución

Compilar el archivo Kotlin:  
kotlinc NombreArchivo.kt -include-runtime -d NombreArchivo.jar


Ejecutar el programa compilado:  
java -jar NombreArchivo.jar



Ejemplo para CuentaBancaria.kt:
kotlinc CuentaBancaria.kt -include-runtime -d CuentaBancaria.jar
java -jar CuentaBancaria.jar

Commits Recomendados

Cuenta Bancaria  
git add CuentaBancaria.kt
git commit -m "Añadir clase CuentaBancaria con validaciones de saldo y retiro"


Producto  
git add Producto.kt
git commit -m "Añadir clase Producto con validación de precio y descuento"


Figuras  
git add Figuras.kt
git commit -m "Añadir clases Cuadrado, Rectángulo y Círculo con métodos de área y perímetro"


Biblioteca  
git add Biblioteca.kt
git commit -m "Implementar sistema básico de gestión de biblioteca con usuarios y préstamos"



Autor
Yabar Carazas Melvin JarredIngeniería de Software – 6° semestreFecha: 02/09/2025
