#ifndef GLOBAL_H
#define GLOBAL_H

#define ORGANISATION     ("FredericVansteenkiste")
#define NAME_APPLICATION ("Imager")

// La fonction suivante permet de changer la valeur d'un élément r, g ou b d'une
// couleur, de telle façon que le pointillé servant à encadrer l'image soit
// toujours visible par rapport à l'arrière plan
// La valeur d'entrée doit être comprise entre 0 et 255.
// L'algorithme ajoute 128 à la valeur d'entrée puis retire 256 si nécessaire
// pour borner la valeur de sortie dans l'intervalle [0, 255]
int iRevertColor(const int& iColor);

#endif // GLOBAL_H
