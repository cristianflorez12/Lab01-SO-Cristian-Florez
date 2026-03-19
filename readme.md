## Informe en el archivo llamado: Informe Lab 1 - Sistemas Operativos y Lab - Cristian Florez

## Pruebas realizadas

### wcat

Caso: Archivo único
Comando:
./wcat file1.txt

Caso: Múltiples archivos
Comando:
./wcat file1.txt file2.txt

Caso: Archivo vacío
Comando:
./wcat empty.txt

Caso: Archivo inexistente (manejo de error)
Comando:
./wcat noexiste.txt

Caso: Sin argumentos
Comando:
./wcat

---

### wgrep

Caso: Búsqueda básica
Comando:
./wgrep foo file1.txt

Caso: Búsqueda en múltiples archivos
Comando:
./wgrep foo file1.txt file2.txt

Caso: Sensibilidad a mayúsculas/minúsculas
Comando:
./wgrep Foo file2.txt

Caso: Sin coincidencias
Comando:
./wgrep xyz file1.txt

Caso: Lectura desde entrada estándar (stdin)
Comando:
echo "foo\nbar\nfoo123\nzzz" | ./wgrep foo

Caso: Archivo con líneas largas
Comando:
./wgrep a longline.txt

Caso: Cadena vacía como término de búsqueda
Comando:
./wgrep "" file1.txt

Caso: Sin argumentos (error)
Comando:
./wgrep

Caso: Archivo inexistente (error)
Comando:
./wgrep foo noexiste.txt

---

### wzip

Caso: Compresión de un archivo
Comando:
./wzip file1.txt > test.z

Caso: Compresión de múltiples archivos
Comando:
./wzip file1.txt file2.txt > test.z

Caso: Archivo vacío
Comando:
./wzip empty.txt > test.z

Caso: Archivo con caracteres repetidos
Comando:
./wzip repeated.txt > test.z

Caso: Continuidad entre archivos (RLE)
Comando:
./wzip file3.txt file4.txt > test.z

---

### wunzip

Caso: Descompresión básica
Comando:
./wunzip test.z

---

### Prueba de integración (wzip + wunzip)

Caso: Compresión y descompresión completa
Comando:
./wzip longline.txt repeated.txt > test.z
./wunzip test.z
