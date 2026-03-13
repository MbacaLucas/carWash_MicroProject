# 🏎️ Car Wash Management System (C++ Relational Model)

![C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat-square&logo=c%2B%2B)
![Logic](https://img.shields.io/badge/Logic-Relational-orange.svg?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)

Un sistema de gestión para estaciones de lavado de autos que implementa un modelo de datos relacional en memoria. Este proyecto destaca por la separación de entidades y el uso de algoritmos avanzados de la STL para procesar transacciones.

## 🧠 Desafío de Ingeniería
El reto principal de este software fue la **Integridad Relacional**. A diferencia de sistemas simples, aquí el precio y el nombre del servicio no residen en el registro de venta, sino en un **Catálogo Maestro**. El sistema debe "unir" (Join) estas tablas en tiempo real para generar reportes y cálculos financieros.



## 🚀 Características Destacadas
* **Modelo Relacional**: Uso de `serviceId` como Llave Foránea (Foreign Key) para vincular ventas con servicios.
* **Búsqueda Dinámica con STL**: Implementación de `std::find_if` con capturas de lambda para recuperar información del catálogo durante la ejecución.
* **Cálculos Complejos**: Uso de `std::accumulate` con una lambda personalizada que realiza búsquedas internas para calcular el ingreso total sin duplicar datos de precio.
* **Interfaz de Usuario Robusta**: Sistema de validación de entrada mediante bucles `do-while` para asegurar la integridad de los IDs ingresados.

## 🛠️ Tecnologías Aplicadas
* **C++17 Standard**
* **Standard Template Library (STL)**: `<vector>`, `<algorithm>`, `<numeric>`.
* **Formateo de Datos**: `<iomanip>` para reportes tabulares alineados profesionalmente.

## 📊 Ejemplo de Funcionamiento
```text
ID   Customer Name            Service        Price
=======================================================
1    Roberto Gomez            Premium Wash   $20.00
2    Ana Martinez             VIP            $35.00
3    Luis Herrera             Basic Wash     $10.00
-------------------------------------------------------
                          TOTAL REVENUE: $65.00
