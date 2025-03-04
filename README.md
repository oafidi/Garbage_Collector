# README: Implémentation de deux Garbage Collectors en C

Ce document explique l'implémentation de deux algorithmes de Garbage Collection en C : un GC simple avec libération manuelle et un GC de type Mark and Sweep. Ces deux approches gèrent dynamiquement la mémoire pour éviter les fuites.

## 1. Garbage Collector Simple (gc.h)

### Fonctionnement

- **Allocation :** `gc_malloc(size, function)` alloue de la mémoire et l'ajoute à une liste chaînée.
- **Libération :** Quand `function` vaut 0, toutes les allocations sont libérées.

### Points Clés

- Aucune détection automatique des objets inutilisés.
- Idéal pour des cas simples avec libération globale.

### Exemple d'utilisation

```c
char *str = gc_malloc(2, 1);
str[0] = 'a';
str[1] = '\0';

printf("%p\n", str);
gc_malloc(0, 0); // Libère toute la mémoire
printf("%p\n", str);
```

---

## 2. Garbage Collector Mark and Sweep (mark\_sweep.h)

### Fonctionnement

- **Allocation :** `gc_malloc` alloue la mémoire et l'ajoute à la liste.
- **Marquage :** `gc_mark` marque les objets encore utilisés.
- **Balayage :** `gc_sweep` libère les objets non marqués.
- **Réinitialisation :** `gc_reset_marks` remet les marqueurs à 0.

### Points Clés

- Détecte et libère les objets inaccessibles.
- Simule un vrai ramasse-miettes avec marquage.

### Exemple d'utilisation

```c
MemoryManger *manager = init_MemoryManager();
char *ptr1 = gc_malloc(manager, 4);
char *ptr2 = gc_malloc(manager, 12);

gc_mark(manager, ptr1);
gc_sweep(manager); // ptr2 est libéré

read_memory(manager); // Affiche la mémoire restante
free(manager);
```

---

## Comparaison des deux approches

| **Aspect**               | **Simple GC**                        | **Mark and Sweep GC**                     |
| ------------------------ | ------------------------------------ | ----------------------------------------- |
| **Complexité**           | Simple (à base de liste chaînée)     | Plus complexe (marquage & balayage)       |
| **Détection des fuites** | Non                                  | Oui                                       |
| **Performance**          | Rapide, mais libération globale      | Plus lent, mais libération sélective      |
| **Usage recommandé**     | Petits programmes, libération unique | Projets plus grands avec gestion complexe |

Ces deux GC offrent une excellente base pour comprendre la gestion de mémoire en C et peuvent être améliorés selon vos besoins.



