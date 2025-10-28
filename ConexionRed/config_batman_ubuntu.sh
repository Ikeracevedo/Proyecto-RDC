#!/bin/bash
# ==============================
# Configuración BATMAN-adv - Nodo Ubuntu/Debian
# ==============================

IFACE="wlan0"        # Cambia si tu interfaz tiene otro nombre (usa 'iwconfig' o 'ip a')
SSID="AGRO-MESH"     # Nombre de la red mesh
FREQ=2412            # Frecuencia (canal 1, 2.4 GHz)
IP="10.0.0.1/24"     # IP del nodo dentro de la malla

echo "[INFO] Configurando interfaz WiFi..."
sudo ip link set $IFACE down
sudo iw dev $IFACE set type mp             # mp = mesh point (modo 802.11s)
sudo ip link set $IFACE up
sudo iw dev $IFACE mesh join $SSID freq $FREQ

echo "[INFO] Cargando módulo BATMAN-adv..."
sudo modprobe batman-adv

echo "[INFO] Creando interfaz bat0..."
sudo ip link add bat0 type batadv
sudo batctl if add $IFACE
sudo ip link set up dev $IFACE
sudo ip link set up dev bat0
sudo ip addr add $IP dev bat0

echo "[INFO] Nodo Ubuntu conectado a la red BATMAN con IP $IP"
echo "[INFO] Usa 'ping 10.0.0.2' para probar conexión con Fedora."
