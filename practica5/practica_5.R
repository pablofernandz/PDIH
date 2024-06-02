library(tuneR)
library(seewave)
library(audio)


# 1. Leer ficheros de sonido (wav):
Nombre <- readWave('nombre.wav')
Apellido <- readWave('apellido.wav')


# 2. Dibujar la forma de onda de ambos sonidos
round(length(Nombre@left) / Nombre@samp.rate, 3)
total_samples_Nombre <- length(Nombre@left)
plot(extractWave(Nombre, from = 1, to = total_samples_Nombre))

round(length(Apellido@left) / Apellido@samp.rate, 3)
total_samples_Apellido <- length(Apellido@left)
plot(extractWave(Apellido, from = 1, to = total_samples_Apellido))


# 3. Información de las cabeceras de ambos sonidos
Nombre
Apellido


# 4. Unir ambos sonidos en uno nuevo
NombreApellido <- pastew(Apellido, Nombre , output="Wave")


# 5. Dibujar la forma de onda de la señal resultante
round(length(NombreApellido@left) / NombreApellido@samp.rate, 3)
total_samples_NombreApellido <- length(NombreApellido@left)
plot(extractWave(NombreApellido, from = 1, to = total_samples_NombreApellido))


# 6. Filtro de frecuencia entre 10000Hz y 20000Hz
NombreApellidoFiltrado <- bwfilter(NombreApellido, 48000, channel = 1, n = 1, from =  10000,
                                    to = 20000, bandpass = TRUE, listen = FALSE, output = "Wave")


# 7. Almacenar la señal obtenida como un fichero WAV denominado "mezcla.wav"
writeWave(NombreApellidoFiltrado, file.path("mezcla.wav"))


# 8. Cargar un nuevo archivo de sonido
Edad <- readWave('edad.wav')

# aplicarle eco:
EdadEco <- echo(Edad,f=22050,amp=c(0.8,0.4,0.2),delay=c(1,2,3),
                      output="Wave")
EdadEco@left <- 10000 * EdadEco@left

# darle la vuelta al sonido
EdadEcoAlreves <- revw(EdadEco, output="Wave")

# Almacenar la señal obtenida como un fichero WAV denominado "alreves.wav"
writeWave(EdadEcoAlreves, file.path("alreves.wav"))

