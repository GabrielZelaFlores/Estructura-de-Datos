
# Proyecto 2 Kotlin POO

Este proyecto contiene cuatro programas desarrollados en **Kotlin** aplicando conceptos de **Programación Orientada a Objetos (POO)**.  

## Contenido

1. **Cuenta Bancaria**  
   Simula una cuenta bancaria con saldo y límite de retiro. Valida operaciones de retiro según reglas.

2. **Producto**  
   Representa un producto con precio y porcentaje de descuento, validando valores y calculando el precio final.

3. **Figuras**  
   Implementa clases para **cuadrado, rectángulo y círculo**, con métodos para calcular área y perímetro.

4. **Biblioteca**  
   Sistema básico con materiales (libros, revistas), usuarios y operaciones de préstamo y devolución.

---

## Ejecución en Git Bash

1. Compilar el archivo Kotlin:  
   kotlinc NombreArchivo.kt -include-runtime -d NombreArchivo.jar

2. Ejecutar el programa compilado:

   ```bash
   java -jar NombreArchivo.jar
   ```

> Ejemplo para **CuentaBancaria.kt**:

kotlinc CuentaBancaria.kt -include-runtime -d CuentaBancaria.jar
java -jar CuentaBancaria.jar

## Commits recomendados

* **Cuenta Bancaria**
  
  git add CuentaBancaria.kt
  
  git commit -m "Añadir clase CuentaBancaria con validaciones de saldo y retiro"
  ```

* **Producto**

  git add Producto.kt
  git commit -m "Añadir clase Producto con validación de precio y descuento"
  ```

* **Figuras**

  git add Figuras.kt
  git commit -m "Añadir clases Cuadrado, Rectángulo y Círculo con métodos de área y perímetro"
  ```

* **Biblioteca**

  git add Biblioteca.kt
  git commit -m "Implementar sistema básico de gestión de biblioteca con usuarios y préstamos"
  ```

---

## Autor

**Yabar Carazas Melvin Jarred**
Ingeniería de Software – 6° semestre
Fecha: 02/09/2025

```
