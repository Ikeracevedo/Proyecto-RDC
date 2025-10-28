#!/bin/bash
# ==============================
# Configuración BATMAN-adv - Nodo Fedora (Servidor)
# ==============================

IFACE="wlan0"
SSID="AGRO-MESH"
FREQ=2412
IP="10.0.0.2/24"

echo "[INFO] Configurando interfaz WiFi..."
sudo ip link set $IFACE down
sudo iw dev $IFACE set type mp
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

echo "[INFO] Nodo Fedora conectado a la red BATMAN con IP $IP"
echo "[INFO] Usa 'ping 10.0.0.1' para probar conexión con Ubuntu."
