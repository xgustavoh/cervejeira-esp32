# Cervejeira Wi-Fi

Este projeto consiste no firmware de uma controladora para geladeira/cervejeira.
Para esse projeto será usado uma `ESP32` como controladora e uma `Raspberry Pi 2` com servidor (broker) do MTQQ + Site.

## Componentes:

| COD  | IN/OUT | GPIO |          Tipo           | Descrição                        |
| :--: | :----: | :--: | :---------------------: | :------------------------------- |
| #R01 |  OUT   |  X   |          Relé           | Cooler - 1                       |
| #R02 |  OUT   |  X   |          Relé           | Cooler - 2                       |
| #R03 |  OUT   |  X   |          Relé           | Cooler - 3                       |
| #R04 |  OUT   |  X   |          Relé           | Motor de Partida                 |
| #R05 |  OUT   |  X   |          Relé           | Motor (_OPCIONAL_)               |
| #R06 |  OUT   |  X   |          Relé           | Resistencia degelo               |
| #T01 |   IN   |  X   |  Sensor de Temperatura  | Temperatura antes do Radiador    |
| #T02 |   IN   |  X   |  Sensor de Temperatura  | Temperatura do Radiador          |
| #T03 |   IN   |  X   |  Sensor de Temperatura  | Temperatura apos o Radiador      |
| #T04 |   IN   |  X   |  Sensor de Temperatura  | Temperatura no meio da Geladeira |
| #I01 |   IN   |  X   |  Interruptor (Switch)   | Interruptor porta aberta         |
| #B01 |   IN   |  X   | Sensor de Nível de Água | Reservatorio de agua do degelo   |
