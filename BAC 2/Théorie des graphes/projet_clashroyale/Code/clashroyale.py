import networkx as nx
import matplotlib.pyplot as plt
import sys
from enum import Enum

def creer_graphe_type(fichier, type_carte=None):
    # Création d'un graphe non orienté
    graphe_type = nx.Graph()

    # Ouverture du fichier en mode lecture
    with open(fichier, 'r') as file:
        # Lecture de toutes les lignes du fichier
        lignes = file.readlines()

        # Parcours de chaque ligne du fichier
        for line in lignes:
            # Suppression des espaces avant et après la ligne, puis séparation des mots
            cartes = line.strip().split()

            # Vérification si le nombre de cartes est pair (nom et type)
            if len(cartes) % 2 != 0:
                # Ignorer les lignes qui n'ont pas le format attendu
                print("Erreur dans la lecture d'un élément du fichier texte.")
                continue

            # Filtrage des cartes du type spécifié
            if type_carte:
                cartes_du_type = [cartes[i] for i in range(0, len(cartes), 2) if cartes[i + 1] == type_carte]
            else:
                # Si aucun type spécifié, prendre toutes les cartes
                cartes_du_type = cartes[::2]  

            # Ajout de tous les sommets (cartes du type spécifié ou toutes les cartes) au graphe
            graphe_type.add_nodes_from(cartes_du_type)

            # Ajout d'arêtes pondérées entre les cartes du même deck
            for i, carte1 in enumerate(cartes_du_type):
                for j, carte2 in enumerate(cartes_du_type):
                    if i < j:
                        # Si l'arête existe déjà, incrémenter le poids
                        if graphe_type.has_edge(carte1, carte2):
                            graphe_type[carte1][carte2]['weight'] += 1
                        else:
                            # Sinon, ajouter une nouvelle arête avec un poids initial de 1
                            graphe_type.add_edge(carte1, carte2, weight=1)

    # Retourne le graphe construit
    return graphe_type


# Affiche le graphe basé sur le fichier
def afficher_graphe(graph):
    pos = nx.circular_layout(graph)  # Dispose les sommets
    labels = nx.get_edge_attributes(graph, 'weight')
    nx.draw(graph, pos, with_labels=True, node_size=500, node_color='skyblue', node_shape='')
    nx.draw_networkx_nodes(graph, pos, node_color='skyblue', node_size=800, node_shape='')
    nx.draw_networkx_edge_labels(graph, pos, edge_labels=labels)
    # Définir une couleur différente pour le texte des étiquettes
    node_labels = {node: node for node in graph.nodes}
    font_color = 'red'

    #Ajoute les étiquettes aux sommets avec la couleur définie
    nx.draw_networkx_labels(graph, pos, labels=node_labels, font_color=font_color)
    plt.show()

# Affiche les 3 cartes les plus jouées
def cartes_les_plus_jouees(graph):
     # Calculer la somme des poids des arêtes pour chaque nœud
    sommes_ponderation = dict(graph.degree(weight='weight'))

    # Trouver les trois nœuds les plus joués
    top_cartes = sorted(sommes_ponderation.items(), key=lambda x: x[1], reverse=True)[:3]

    return top_cartes

# Affiche les 3 couples de cartes les plus joués
def couple_cartes_plus_joues_ensemble(graph):
    # Créez une liste de toutes les arêtes avec leurs poids
    poids_aretes = [(edge, graph[edge[0]][edge[1]]['weight']) for edge in graph.edges()]

    # Triez la liste en fonction des poids des arêtes (du plus grand au plus petit)
    plus_grandes_ponderations = sorted(poids_aretes, key=lambda x: x[1], reverse=True)[:3]

    return plus_grandes_ponderations

# Affiche les couples de cartes jamais jouées ensemble
def couples_cartes_jamais_joues(graph):
    # Créer une liste de toutes les paires de cartes possibles
    paires_cartes= [(card1, card2) for card1 in graph.nodes for card2 in graph.nodes if card1 != card2]

    # Trouver les paires de cartes qui n'ont jamais été jouées ensemble
    couples_jamais_joues = [couple for couple in paires_cartes if not graph.has_edge(*couple)]

    return couples_jamais_joues

# Affiche le nombre d'Erdos pour la carte la plus jouée
def nombre_erdos_carte_plus_jouee(graph):
    # Trouver la carte la plus jouée
    tmp = cartes_les_plus_jouees(graph)
    carte_plus_jouee = tmp[0][0]

    # Calculer le nombre d'Erdos pour chaque carte par rapport à la carte la plus jouée
    nombres_dErdos = {}
    for carte in graph.nodes:
        if carte != carte_plus_jouee:
            nombre_dErdos = nx.shortest_path_length(graph, source=carte_plus_jouee, target=carte)
            nombres_dErdos[carte] = nombre_dErdos

    return nombres_dErdos

# Grace au nombre Erdos on peut determiner certaines cartes les moins jouées.
def certaines_cartes_moins_jouees(graph):
    nombre_dErdos = nombre_erdos_carte_plus_jouee(graph)

    # Calculer le nombre total de connexions pour chaque carte
    connexions_totales = dict(graph.degree())

    # Normaliser le nombre d'Erdős en fonction du nombre total de connexions
    nbr_dErdos_normalise = {carte: nombre_dErdos / (connexions_totales[carte] + 1) for carte, nombre_dErdos in nombre_dErdos.items()}

    # Trouver le nombre d'Erdős minimum
    nbr_dErdos_normalise_max = max(nbr_dErdos_normalise.values())

    # Sélectionner toutes les cartes avec le nombre d'Erdős minimum normalisé
    certaines_cartes_moins_jouees = [cartes for cartes, nbr_dErdos_normalise in nbr_dErdos_normalise.items() if nbr_dErdos_normalise == nbr_dErdos_normalise_max]

    return certaines_cartes_moins_jouees

# Affiche les cartes les moins jouées
def cartes_moins_jouees_manquantes(graph):
    # Calculer la somme des poids des arêtes pour chaque nœud
    somme_poids_noeuds = dict(graph.degree(weight='weight'))

    # Trouver les cartes avec la somme des poids des arêtes la plus basse
    somme_min = min(somme_poids_noeuds.values())
    cartes_moins_jouees = [carte for carte, somme_poids in somme_poids_noeuds.items() if somme_poids == somme_min]

    return cartes_moins_jouees

# Affiche si le graphe fourni est eulérien
def est_eulerien(graph):
    # Vérifier si chaque sommet a un degré pair
    for sommet in graph.nodes():
        if graph.degree(sommet) % 2 != 0:
            return False
    return True

# Vérifie si le graphe est hamiltonien en utilisant le théorème de Dirac
def est_hamiltonian_dirac(graph):
    n = len(graph.nodes)
    
    for sommet in graph.nodes:
        if graph.degree(sommet) < n/2:
            return False
    
    return True

class Mode(Enum):
    CREER = 1
    TOP3CARTES = 2
    TOP3COUPLECARTES = 3
    ERDOS = 4
    CARTEMOINSJOUEESMANQUANTES = 5
    CERTAINESCARTESMOINSJOUEES = 6
    COUPLEJAMAISJOUE = 7
    EULER = 8
    HAMILTONIEN = 9


OPTIONS = {
    "-c": Mode.CREER,
    "-TOP3C": Mode.TOP3CARTES,
    "-TOP3CC": Mode.TOP3COUPLECARTES,
    "-ERDOS": Mode.ERDOS,
    "-CMJM": Mode.CARTEMOINSJOUEESMANQUANTES,
    "-CCMJ": Mode.CERTAINESCARTESMOINSJOUEES,
    "-CJJ": Mode.COUPLEJAMAISJOUE,
    "-EULER": Mode.EULER,
    "-HAMIL": Mode.HAMILTONIEN,
}

if len(sys.argv) not in [2, 3] or sys.argv[1] not in OPTIONS:
    sys.stdout.write("./clashroyale.py <operation> [type_carte]\n")
    sys.stdout.write("     où <operation> peut-être -c, -TOP3C, -TOP3CC, -ERDOS, -CMJM, -CCMJ, -CJJ, -EULER, -HAMIL\n")
    sys.stdout.write("     et où [type_carte] peut uniquement être utilisé après -c et -TOP3CC et peut être -AER (Aériennes), -TER (Terrestres), -BAT (Batiments), -SOR (Sorts)\n\n")
    sys.stdout.write("                       ##############~EXEMPLES~##############\n\n")
    sys.stdout.write("  ./clashroyale.py -c: Affiche le graphe des cartes et leurs arêtes pondérées.\n")
    sys.stdout.write("  ./clashroyale.py -c -AER: Affiche le graphe des cartes de type Aériennes et leurs arêtes pondérées (Fonctionne avec les 4 types de cartes).\n")
    sys.stdout.write("  ./clashroyale.py -TOP3C: Affiche les 3 cartes les plus jouées.\n")
    sys.stdout.write("  ./clashroyale.py -TOP3CC: Affiche le top 3 des couples de cartes les plus jouées.\n")
    sys.stdout.write("  ./clashroyale.py -TOP3CC -TER: Affiche le top 3 des couples de cartes du type Terrestres les plus jouées (Fonctionne avec les 4 types de cartes).\n")
    sys.stdout.write("  ./clashroyale.py -ERDOS Affiche le nombre d'Erdos en prenant comme référence la carte la plus jouée.\n")
    sys.stdout.write("  ./clashroyale.py -CMJM: Affiche les couples de cartes les moins joués manquantes.\n")
    sys.stdout.write("  ./clashroyale.py -CCMJ: Affiche certaines cartes les moins jouées.\n")
    sys.stdout.write("  ./clashroyale.py -CJJ: Affiche les couples de cartes jamais joués ensemble.\n")
    sys.stdout.write("  ./clashroyale.py -EULER: Précise si le graphe est eulérien ou non.\n")
    sys.stdout.write("  ./clashroyale.py -HAMIL: Précise si le graphe est hamiltonien si il l'est peut-être mais ne respecte pas la condition du théorème de Dirac.\n")

    exit("Mauvais arguments\n")

mode = OPTIONS[sys.argv[1]]
if len(sys.argv) == 3 :
    if(sys.argv[2] == "-AER"):
        type_carte = "TrAerienne"
    elif(sys.argv[2] == "-BAT"):
        type_carte = "Batiments"
    elif(sys.argv[2] == "-TER"):
        type_carte = "TrTerrestre"
    elif(sys.argv[2] == "-SOR"):
        type_carte = "Sorts"
    else:
        type_carte = ""
        exit(f"Mauvais argument : {sys.argv[2]}")

if mode == Mode.CREER:
    if len(sys.argv) == 3:
            graph = creer_graphe_type("decks", type_carte)
            afficher_graphe(graph)
    else:
            graph = creer_graphe_type("decks")
            afficher_graphe(graph)

elif mode == Mode.TOP3CARTES:
    nbElementParLigne = 8
    graph = creer_graphe_type("decks")

    top_cartes = cartes_les_plus_jouees(graph)

    for i, (cartes, sommePonderation) in enumerate(top_cartes, 1):
        print(f"TOP {i}: {cartes} avec {sommePonderation // (nbElementParLigne - 1)} occurrences")

elif mode == Mode.TOP3COUPLECARTES:
    if len(sys.argv) == 3:
        graph = creer_graphe_type("decks", type_carte)
    else:
        graph = creer_graphe_type("decks")
    top_ponderation = couple_cartes_plus_joues_ensemble(graph)
    if not top_ponderation:
        print(f"Aucune carte du type {type_carte} n'est jouée dans un même deck.")
    # Affiche les trois couples de cartes les plus joués avec le poids de l'arête
    for i, (arete, ponderation) in enumerate(top_ponderation, 1):
        print(f"TOP {i}: {arete} avec un poids d'arête de {ponderation}")

elif mode == Mode.ERDOS:
    graph = creer_graphe_type("decks")
    nombres_erdos = nombre_erdos_carte_plus_jouee(graph)
    # Affiche le nombre d'Erdos basé sur la carte la plus jouée
    for cartes, nombres_erdos in nombres_erdos.items():
        print(f"Le nombre d'Erdős par rapport à {cartes} est : {nombres_erdos}")

elif mode == Mode.CARTEMOINSJOUEESMANQUANTES:
    graph = creer_graphe_type("decks")
    
    # Trouver toutes les cartes les moins jouées
    moins_jouees_cartes = cartes_moins_jouees_manquantes(graph)
    
    # Trouver certaines cartes les moins jouées
    certaines_cartes_moins_jouees = certaines_cartes_moins_jouees(graph)
    
    # Identifier les cartes qui sont dans least_cards mais pas dans certaines_cartes_moins_jouees
    moins_jouees_cartes_restantes = set(moins_jouees_cartes) - set(certaines_cartes_moins_jouees)
    
    # Afficher les cartes restantes
    for i, cartes in enumerate(moins_jouees_cartes_restantes, 1):
        print(f"Les cartes manquantes sont : {cartes}")

elif mode == Mode.CERTAINESCARTESMOINSJOUEES:
    graph = creer_graphe_type("decks")
    certaines_cartes_moins_jouees_resultat = certaines_cartes_moins_jouees(graph)
    # Affiche certaines cartes les moins jouées en fonction du nombre d'Erdos
    for i, cartes in enumerate(certaines_cartes_moins_jouees_resultat, 1):
        print(f"Certaines cartes moins jouées basées sur le nombre d'Erdos : {cartes}")

elif mode == Mode.COUPLEJAMAISJOUE:
    graph = creer_graphe_type("decks")
    couples_jamais_joues = couples_cartes_jamais_joues(graph)
    # Affiche les couples de cartes jamais jouées ensemble
    for i, couple in enumerate(couples_jamais_joues, 1):
        print(f"Pair {i}: {couple[0]} - {couple[1]}")

elif mode == Mode.EULER:
    graph = creer_graphe_type("decks")
    # Affiche si un graphe est eulérien ou non
    if est_eulerien(graph):
        print(f"Le graphe est eulérien")
    else:
        print(f"Le graphe n'est pas eulérien")

elif mode == Mode.HAMILTONIEN:
    graph = creer_graphe_type("decks")
    if est_hamiltonian_dirac(graph):
        print(f"Le graphe est hamiltonien")
    else:
        print(f"Le graphe est peut-être hamiltonien mais ne respecte pas la condition du théorème de Dirac")