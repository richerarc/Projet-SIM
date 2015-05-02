##Informations au sujet des puzzles

- Un puzzle est un ensemble d'objet contenu dans un endroit restreint.
- Un puzzle contient une boîte de collisions, des entrées, ainsi qu'un quantité d'objet.
- Un puzzle sera créé à partir d'un fichier texte, un .pzl, et tout il sera mis en mémoire dans un InfoPuzzle.
  
##Exemple de fichier texte
puzzle{  
boite{    
x y z  
x y z  
x y z  
x y z  
x y z  
x y z  
x y z  
x y z  
}  
entrees{  
x y z  
x y z  
}  
objet{  
c Pendule.txt    
p x y z  
}    
objet{  
c Pendule.txt    
p x y z  
}    
objet{  
c Pendule.txt    
p x y z   
}    
objet{  
c Pendule.txt    
p x y z  
}       
}; 

- Ce puzzle contienderait 4 pendules à des positions différentes avec deux entrées.
- La boîte de collision du puzzle doit respecter les normes de boîte de collision.
- Il doit y avoir un minimum d'un entrée pour le puzzle et il peut bien sure avoir plus d'un type d'objet.
- Vous devez aller ajouter le nom de votre fichier texte dans le fichier puzzles.txt