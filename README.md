# Taller de Diseño de Software 2023

## Introducción
Este informe presenta un análisis sobre la implementación de un compilador. El enfoque abarca la utilización de herramientas clave como Flex y Bison para definir las reglas y tokens del lenguaje a compilar, la construcción del Abstract Syntax Tree (AST) mediante las reglas de Bison, la implementación del algoritmo de chequeo de tipos, y la generación del Three Address Code y Assembly Code, todos estos últimos llevados a cabo en el lenguaje C.

Este proyecto tiene como objetivo principal no solo mostrar la utilización del compilador con los comandos de ejecución del mismo, sino también proporcionar una visión detallada de cada fase del proceso de construcción. A lo largo del informe, se analizarán minuciosamente los detalles de implementación, capacidades e inconveniencias presentes para posibles mejoras en cada etapa, ofreciendo así una comprensión profunda de las decisiones tomadas durante la implementación.

## 1: Comandos de ejecución

### 1.1: Compilación
```
Poner comandos de compilación.
```

### 1.2: Ejecución
```
Poner comandos de ejecución.
```

### 1.3: Ejecución de Tests
```
Poner comandos de ejecución.
```

## 2: Proceso de construcción.

### 2.1: Reglas del lenguaje.

Flex y Bison desempeñan roles cruciales en la construcción eficiente de un compilador, ofreciendo herramientas para analizar y procesar el código fuente. 

Por un lado, Flex, un generador de analizadores léxicos, permite definir patrones de tokens mediante expresiones regulares, facilitando la identificación y clasificación de elementos léxicos en el código fuente. Esta capacidad resulta fundamental en la primera etapa del proceso, donde se realiza el escaneo del código para identificar palabras clave, identificadores y otros elementos.

Por otro lado, Bison, un generador de analizadores sintácticos, trabaja en conjunto con Flex para construir la gramática del lenguaje a compilar. Bison interpreta las reglas gramaticales definidas mediante una gramática libre de contexto y genera un analizador sintáctico capaz de reconocer la estructura jerárquica del código fuente. Su función principal radica en la construcción de las reglas del lenguaje, mediante Abstract Syntax Tree (AST), que sirve como estructura interna para representar la sintaxis del programa de manera más abstracta y manipulable y del cual se habla próximamente en el informe.

La gramática y tokens del lenguaje se corresponden muy cercanamente a las reglas dadas en la consigna de este proyecto. A continuación se deja el enlace a los archivos en donde se encuentran los mismos:

- [Tokens](parser/lexicon.l)
- [Gramática](parser/syntax.y)

Como se mencionó, para el lenguaje diseñado se busca seguir la consigna dada; sin embargo se realiza una extensión de la gramática para evitar conflictos de shift/reduce y reduce/reduce en la regla de generación de métodos. Dicha extensión consiste en la agregación del token "*TDef*" (`def`) para la definición de métodos; porque el conflicto existía entre la declaración de variables y dicha regla, debido a que las mismas comenzaban con el token "*TType*" (`integer` o `bool`).

### 2.2: Generación del AST.

El Abstract Syntax Tree (AST) es una representación estructurada y jerárquica de la sintaxis de un programa. Simplifica la complejidad gramatical, capturando la lógica semántica y relaciones entre construcciones sintácticas. Cada nodo del AST representa una entidad del código, permitiendo una interpretación clara y facilitando la generación de código intermedio. Es esencial en compiladores para el análisis sintáctico y semántico eficiente del código fuente.

En el caso de este proyecto, el AST se construye tomando provecho del embebimiento del lenguaje C en la herramienta Bison; el cual nos permite tomar un conjunto de conveniencias para representar jerárquicamente la sintaxis de los programas, en conjunto con una estructura implementada en C, a la que denominamos `NodeInfo`. Esta estructura contiene información relevante de cada nodo del AST, como el tag de nodo (Para definir qué regla corresponde al nodo), el valor del mismo, el tipo de dato, el nombre del método o variable, entre otros. A continuación se deja el enlace a las estructuras:

- [Header NodeInfo](include/dataStructures/nodeInfo.h)
- [Source NodeInfo](src/dataStructures/nodeInfo.c)
- [Header AST](include/dataStructures/ast.h)
- [Source AST](src/dataStructures/ast.c)

Además, se implementa una tabla de símbolos para almacenar información de las variables y métodos definidos en el programa. Dicha implementación se realiza a través de una pila de tablas de símbolos, en donde cada tabla representa un nivel de búsqueda, y cada búsqueda que se realice sólo puede hacerse en el nivel propio o niveles inferiores. De esta forma podemos tener una noción de alcance de las variables y métodos definidos en el programa. A continuación se deja el enlace a las estructuras:

- [Header SymbolTable](include/dataStructures/symbolTable.h)
- [Source SymbolTable](src/dataStructures/symbolTable.c)

Otra orientación para el uso de la tabla de símbolos es también para el chequeo de tipos, ya que se puede almacenar información de los tipos de datos de las variables y métodos definidos en el programa. De esta forma, se puede realizar un análisis semántico del código fuente, y detectar errores de tipos en las operaciones realizadas. 

Además, la tabla de símbolos, puede utilizarse como forma de intérprete para poder realizar búsquedas de variables y métodos durante la construcción del árbol y así poder evaluar las expresiones y actualizar los valores de los nodos. En nuestro caso, en la rama `pre-project` del repositorio, se implementa un intérprete del pre-proyecto de la materia, en donde se separa el algoritmo de evaluación de la construcción del AST. A continuación se deja el enlace de dicho algoritmo:

- [Header evaluateAst](https://github.com/ValenButtignol/compiler/blob/pre-project/include/ast.h#L34)
- [Source evaluateAst](https://github.com/ValenButtignol/compiler/blob/pre-project/src/ast.c#L137)

Por último, se implementa una estructura de errores para almacenar parte de los errores semánticos que se encuentren en el código fuente. Dicha estructura se implementa como una lista enlazada, en donde cada nodo representa un error, y contiene información relevante del mismo, como el tipo de error, la línea y columna en donde se encuentra, y el mensaje de error. A continuación se deja el enlace a las estructuras:

- [Header ErrorList](include/dataStructures/errorList.h)
- [Source ErrorList](src/dataStructures/errorList.c)

Si bien la detección de errores es completa y correcta, la utilización de esta estructura no es la más eficaz, ya que no es utilizada para detectar errores sintácticos (De eso se encarga la herramienta Flex, ya que es el analizador léxico), y puede que no detecte todos los errores semánticos ante el primer intento de compilación del lenguaje; ya que por un lado están los errores semánticos que se corresponden al mal uso de identificadores (Principalmente identificadores no declarados), los cuales rompen la estructura del árbol y no permiten seguir con la construcción correcta del mismo, y por otro lado están los errores semánticos que se corresponden al chequeo de tipos, cuyo algoritmo se mencionará a continuación.

### 2.3: Chequeo de tipos.

El chequeo de tipos es una etapa fundamental en la construcción de un compilador, ya que permite detectar errores semánticos en el código fuente. En esta etapa se analiza la estructura del AST, y se verifica que las operaciones realizadas sean válidas, es decir, que los tipos de datos de los operandos sean compatibles con el operador utilizado.

El algoritmo lo que hace es un recorrido del árbol generado, y en cada nodo que tenga una etiqueta apropiada para realizar una operación, se verifica que los tipos de los operandos sean compatibles con el operador utilizado. En caso de que no sean compatibles, se agrega un error a la lista de errores, y se continúa con el recorrido del árbol. A continuación se deja el enlace al algoritmo:

- [Header checkTypes](include/algorithms/checktypes.h)
- [Source checkTypes](src/algorithms/checktypes.c)

Un atributo positivo de emplear este enfoque es que se puede detectar todos los errores semánticos en una sola pasada del árbol, y no se necesita realizar un recorrido del árbol por cada error semántico que se encuentre. Sin embargo, un atributo negativo es que no se puede detectar errores semánticos que se correspondan a identificadores no declarados, ya que el algoritmo no puede continuar con el recorrido del árbol si no se encuentra un identificador declarado.

### 2.4: Generación de código intermedio.

### 2.5: Generación de código ensamblador.

Para la generación de código ensamblador, se implementó una fábrica de instrucciones en C, la cual permite generar instrucciones de ensamblador de forma sencilla. La misma se implementa a través del listado de código intermedio generado en la etapa anterior. A través de diferentes maneras de etiquetar cada comando del código fuente, se puede generar el código ensamblador correspondiente a cada instrucción. A continuación se deja el enlace a la fábrica de instrucciones:

- [Header Assembly Generation](include/algorithms/assemblyCodeGenerator.h)
- [Source Assembly Generation](src/algorithms/assemblyCodeGenerator.c)

## 3: Tests.

Dentro del proyecto se incluyen tests para las etapas más complejas del proceso. Los mismos se encuentran en la carpeta `tests`, y se pueden ejecutar con el comando `make test`. A continuación se deja el enlace a los tests:

- [Tests Check Types](tests/testCheckType.c)
- [Tests Assembly Generation](tests/assemblyTestSuite.c)

También está la test suite para la generación correcta del AST, pero el problema es que, por cuestiones de tiempo, se toma la desición de no implementar casos de tests; debido al esfuerzo que demanda la implementación de los mismos. 

Un factor muy positivo de haber separado los algoritmos (la generación del AST, chequeo de tipos, etc.) es que se pueden realizar tests individualmente de cada etapa, y así poder detectar errores más fácilmente. Además, queda muy sencillo el realizar una verificación exhaustiva de cada etapa, ya que se pueden realizar tests de cada caso de error que se pueda encontrar en el código fuente. Un factor negativo es que la manera de generar cada caso de test manuales requiere de tiempo y esfuerzo, ya que se debe pensar con profundidad cada caso a analizar y cómo realizar dicha aserción.

## 4: Conclusiones.