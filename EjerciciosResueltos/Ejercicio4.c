
/* 

Memoria Compartida
    - Compartimos cache
    - Minimizar efecto de latencia
    - Rápido crear Threads (disponibles datos)
    - Desventajas 1CPU
    - Comunicación
            Control y sincronización
    - fork/join

Memoria Distribuida
    - Podemos compartir memoria paralela
    - Comunicación
            Control y sincronización
            Datos
            Mecanismos resistencia a fallos
    - Muchas CPUs
    - Lento en crear procesos
    - Distribución de información
    - Maestro/Esclavo // Peer-2-Peer

MPI
    Lista de nodos -> Host
    Protocolo -> Comunicación autorizada previa / SSH-> Clave publica / privada
    Asigna valores a los hilos
    Comunicación Directa

*/