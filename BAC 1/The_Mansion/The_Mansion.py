import pygame
import random


##### Constantes #####

NOIR       = (  0,   0,   0)
VERT       = (  9, 106,   9)
BLANC      = (255, 255, 255)
ROUGE      = (255,   0,   0)
BLEU       = (  0,   0, 255)

FENETRE_LARGEUR = 800
FENETRE_HAUTEUR = 550
SOL_EPAISSEUR = FENETRE_HAUTEUR//55
SOL_LONGUEUR = FENETRE_LARGEUR
SOL = (SOL_LONGUEUR, SOL_EPAISSEUR)

TOUCHE_QUITTE = pygame.K_q #Touche pour quitter le jeu
TOUCHE_PAUSE  = pygame.K_p
TOUCHE_HAUT   = pygame.K_UP
TOUCHE_BAS    = pygame.K_DOWN
TOUCHE_GAUCHE = pygame.K_LEFT
TOUCHE_DROITE = pygame.K_RIGHT
TOUCHE_TIR    = pygame.K_a

POSITION_PREMIER_SOL = (0, (FENETRE_HAUTEUR//3) - SOL_EPAISSEUR)
POSITION_DEUXIEME_SOL = (0, (FENETRE_HAUTEUR//3)*2 - SOL_EPAISSEUR)
POSITION_TROISIEME_SOL = (0, FENETRE_HAUTEUR - SOL_EPAISSEUR) 

POSITION_Y_COULOIR3 = (FENETRE_HAUTEUR//10)
POSITION_Y_COULOIR2 = (FENETRE_HAUTEUR//3) - SOL_EPAISSEUR + 70
POSITION_Y_COULOIR1 = (FENETRE_HAUTEUR//3)*2 - SOL_EPAISSEUR + 70

PERSO_LARGEUR = (FENETRE_LARGEUR//10)
PERSO_HAUTEUR = (FENETRE_HAUTEUR//5+10)

ZOMBIE_LARGEUR = (FENETRE_LARGEUR//10)
ZOMBIE_HAUTEUR = (FENETRE_HAUTEUR//5 +10)

ZOMBIE_INTRO_LARGEUR = (FENETRE_HAUTEUR//3) - (FENETRE_HAUTEUR//4 + FENETRE_HAUTEUR//240)
ZOMBIE_INTRO_HAUTEUR = (FENETRE_LARGEUR//5) - 80

PERSO_DEPLACEMENT = 5

BALLE_HAUTEUR = (FENETRE_HAUTEUR//100)
BALLE_LARGEUR = (FENETRE_HAUTEUR//100) + (FENETRE_HAUTEUR//200)

DIMENSION_COEUR = ((FENETRE_HAUTEUR*2)//100) + (FENETRE_HAUTEUR//50)
DIMENSION_PAUSE = (FENETRE_HAUTEUR//3) - (FENETRE_HAUTEUR//4)

INTERVALLE_ZOMBIE = 1100
INTERVALLE_BALLE = 2000
INTERVALLE_COULOIR_BOSS = 3500
INTERVALLE_BONUSMALUS = 10000
BONUS_MALUS_TAILLE = (30, 30)

PAUSE_REPLAY_TEXT = (FENETRE_LARGEUR - 580 ,400)
PAUSE_REPLAY_TEXT2 = (FENETRE_LARGEUR - 570, 420)
PAUSE_CONTINUE_TEXT = (FENETRE_LARGEUR - 350 ,400)
PAUSE_CONTINUE_TEXT2 = (FENETRE_LARGEUR - 340, 420)

GAMEOVER_REPLAY_TEXT = (FENETRE_LARGEUR//2 - 150,500)
GAMEOVER_REPLAY_TEXT2 = (FENETRE_LARGEUR//2 - 150,485)
GAMEOVER_QUIT_TEXT = (FENETRE_LARGEUR//2 + 80,500)
GAMEOVER_QUIT_TEXT2 = (FENETRE_LARGEUR//2 + 80,485)


HAUT = 1
BAS = -1
DROITE = 1
GAUCHE = -1
DROITE_P = 1.5
GAUCHE_P = -1.5

##### Constantes FIN #####

##### Dessine #####

def dessine_court():
    fenetre.blit(IMAGE_FOND,(0,0))
    pygame.draw.rect(fenetre, NOIR,((POSITION_PREMIER_SOL), (SOL)))
    pygame.draw.rect(fenetre, NOIR,((POSITION_DEUXIEME_SOL), (SOL)))
    pygame.draw.rect(fenetre, NOIR,((POSITION_TROISIEME_SOL), (SOL)))

def dessine_fin():
    fenetre.blit(IMAGE_CIMETIERE,(0,0))
    text = police_titre.render('GAME OVER', True, BLANC)
    textLargeur = 80
    fenetre.blit(text, ((FENETRE_LARGEUR)//2 -textLargeur-50, FENETRE_HAUTEUR//3))
    point = 'SCORE: '+ str(killcount)
    scoretext = police_titre.render(point, True, BLANC)
    fenetre.blit(scoretext,((FENETRE_LARGEUR)//2 -textLargeur-45,FENETRE_HAUTEUR//2 - 20))


def dessine_intro():
    fenetre.blit(IMAGE_MANOIR,(0,0))
    fenetre.blit(IMAGE_PERSO_INTRO, (FENETRE_LARGEUR//8 - PERSO_LARGEUR//2 -40, FENETRE_HAUTEUR//2-10))
    fenetre.blit(IMAGE_ZOMBIE_INTRO, ((FENETRE_LARGEUR//8)*5 + PERSO_LARGEUR//2+40, FENETRE_HAUTEUR//2+FENETRE_HAUTEUR//4+15)) 
    fenetre.blit(IMAGE_ZOMBIE_INTRO, ((FENETRE_LARGEUR//8)*5 + PERSO_LARGEUR//2+80, FENETRE_HAUTEUR//2+FENETRE_HAUTEUR//4+15)) 
    fenetre.blit(IMAGE_ZOMBIE_INTRO, ((FENETRE_LARGEUR//8)*5 + PERSO_LARGEUR//2+140, FENETRE_HAUTEUR//2+FENETRE_HAUTEUR//4+15)) 
    fenetre.blit(IMAGE_ZOMBIE_INTRO, ((FENETRE_LARGEUR//8)*5 + PERSO_LARGEUR//2+200, FENETRE_HAUTEUR//2+FENETRE_HAUTEUR//4+15)) 
    titre = police_titre.render('THE MANSION', True, NOIR)
    titre_largeur, titre_hauteur = police_titre.size('THE MANSION')
    fenetre.blit(titre, (FENETRE_LARGEUR//2 - titre_largeur//2, (FENETRE_HAUTEUR - 4*titre_hauteur) // 4))
    message1 = police.render("[Q]uit", True, VERT)
    message1_largeur, message1_hauteur = police.size("[Q]uit")
    fenetre.blit(message1, ((FENETRE_LARGEUR - message1_largeur) // 2, 4 * FENETRE_HAUTEUR  // 5))
    message2 = police.render("Press any key to start...", True, VERT)
    message2_largeur, message2_hauteur = police.size("Press any key to start...")
    fenetre.blit(message2, ((FENETRE_LARGEUR - message2_largeur) // 2, 4 * FENETRE_HAUTEUR // 5 + 1.2 * message1_hauteur))
    
##### Fin Dessine #####

##### Entite, Animations #####

def nouvelleEntite():
    return {
        'visible':False,
        'position': [0, 0],
        'imageAffichee':None,
        'poses': [],
        'couloir': 2,
        'id' : 0,
        'vitesse' : 0
    }

def visible(entite):
    entite['visible'] = True


def invisible(entite):
    entite['visible'] = False


def estVisible(entite):
    return entite['visible']


def place(entite, x, y):
    entite['position'][0] = x
    entite['position'][1] = y


def vitesse(entite,v):
    entite['vitesse']=v
    return entite['vitesse']


def position(entite):
    return entite['position']


def ajoutePose(entite, image):
    entite['poses'].append(image)


def prendsPose(entite, pose):
    entite['imageAffichee'] = entite['poses'][pose]
    visible(entite)

def rectangle(entite):
    return entite['imageAffichee'].get_rect().move(entite['position'][0], entite['position'][1])

def dessine(entite, ecran):
    ecran.blit(entite['imageAffichee'], entite['position'])

##### Fin Entite, Animations #####

##### Scene #####

def nouvelleScene():
    return {
        'acteurs': []
    }

def ajouteEntite(scene, entite):
    scene['acteurs'].append(entite)

def enleveEntite(scene, entite):
    acteurs = scene['acteurs']
    if entite in acteurs:
        acteurs.remove(entite)


def acteurs(scene):
    return list(scene['acteurs'])

def miseAJour(scene):
    maScene = acteurs(scene)
    for entite in maScene:
        if entite['id']==1:
            deplace(entite, DROITE)
        elif entite['id']!=1 and entite['id']!=0:
            deplace(entite, GAUCHE)

def affiche(scene, ecran):
    entites = acteurs(scene)
    for objet in entites:
        if estVisible(objet):
            dessine(objet, ecran)

##### Fin Scene #####

##### Entrees #####

def traite_entrees_gameover():
    global gameover, fini, joue
    for evenement in pygame.event.get():
            if evenement.type == pygame.QUIT:
                gameover = False
                fini = True
            if evenement.type == pygame.KEYDOWN:
                if evenement.key == pygame.K_o:
                    joue = False
                    reset_game()
                if evenement.key == TOUCHE_QUITTE:
                    gameover = False
                    fini = True

def traite_entrees():
    global joue, fini, indice, pause, maintenant, prochain, delai, temps_restant, temps_pause_malus
    for evenement in pygame.event.get():
        if evenement.type == pygame.QUIT:
            joue = False
            fini = True
        if evenement.type == pygame.KEYDOWN:
            joue = True
            if evenement.key == TOUCHE_QUITTE:
                joue = False
                fini = True
            if evenement.key == TOUCHE_TIR:
                if pause==False:
                    if prochain<maintenant:
                        prochain = maintenant + delai
                        if indice == 0:
                            indice = 1
                        if indice == 2:
                            indice = 3
                        if indice == 4:
                            indice = 5
                        nouveauTir()
            if evenement.key == TOUCHE_HAUT:
                if pause==False:
                    couloir_plus(perso)
            if evenement.key == TOUCHE_BAS:
                if pause==False:
                    couloir_moins(perso)
            if evenement.key == TOUCHE_DROITE:
                if pause==False:                   
                    deplace(perso, DROITE_P)
            if evenement.key == TOUCHE_GAUCHE:
                if pause==False:
                    deplace(perso, GAUCHE_P)
            if evenement.key == pygame.K_o:
                if pause:
                    reset_game()
            if evenement.key == TOUCHE_PAUSE:
                if pause == False:
                    pause = True
                    if maintenant<temps_precedent:
                        temps_pause_malus=temps_precedent-maintenant
                    if maintenant<fin_tir_rapide:
                        temps_restant=fin_tir_rapide-maintenant
                    if maintenant<fin_tir_lent:
                        temps_restant=fin_tir_lent-maintenant
                    for entite in acteurs(scene):
                        vitesse(entite, 0)
                else:
                    for entite in acteurs(scene):
                        if entite['id']==4:
                            vitesse(entite, -vit_balle_boss)
                        if entite['id']==3:
                            vitesse(entite, vit_zombie_boss)
                        if entite['id']==2:
                            vitesse(entite, vit_zombie)
                        if entite['id']==1:
                            vitesse(entite, vit_balle)
                        if entite['id']==0:
                            vitesse(entite, PERSO_DEPLACEMENT)
                    pause = False
 

##### Fin Entrees #####

##### Mouvements #####

def deplace(entite, sens):
    entite['position'][0] += entite['vitesse']*sens

def couloir_plus(entite):
    entite['couloir']+=1
    if entite['couloir']>3:
        entite['couloir']=3

def couloir_moins(entite):
    entite['couloir']-=1
    if entite['couloir']<1:
        entite['couloir']=1

def couloir_perso_et_boss(entite):
    if entite['couloir']==1:
        entite['position'][1]=POSITION_Y_COULOIR1
    if entite['couloir']==2:
        entite['position'][1]=POSITION_Y_COULOIR2
    if entite['couloir']==3:
        entite['position'][1]=POSITION_Y_COULOIR3

def limite_horiz():
    if perso['position'][0]>1025:
        perso['position'][0]=1025
    if perso['position'][0]<0:
        perso['position'][0]=0

def limite_entite():
    global life
    for entite in acteurs(scene):
        if entite['position'][0]>FENETRE_LARGEUR+100:
            enleveEntite(scene, entite)
        elif entite['position'][0]<-20:
            enleveEntite(scene, entite)
            if entite['id']==2:
                life -=1
            if entite['id']==3:
                life=0

##### Fin Mouvements #####

##### Collision #####

def collision():
    global killcount, vit_zombie, life, life_boss, recal, delai, fin_tir_rapide, fin_tir_lent, fin_speedplus_affichage, fin_speedmoins_affichage, indice
    for entite in acteurs(scene):
        if entite != perso and entite['id']!=1 and rectangle(perso).colliderect(rectangle(entite)):
            enleveEntite(scene, entite)
            if entite['id']==3:
                life=0
            if entite['id']!=5 and entite['id']!=6 and entite['id']!=7 and entite['id']!=8 and entite['id']!=9:
                life-=1
            if entite['id']==5:
                indice = 4
                delai =50
                fin_tir_rapide = maintenant+10000
            if entite['id']==6:
                if vit_zombie>3:
                    vit_zombie-= 1
                    fin_speedmoins_affichage=maintenant+2000
            if entite['id']==7:
                indice = 2
                delai=300
                fin_tir_lent = maintenant+10000
            if entite['id']==8:
                vit_zombie+=2
                fin_speedplus_affichage=maintenant+2000
            if entite['id']==9:
                life+=1
        if entite['id']==1:
            for o in acteurs(scene):
                if o != perso and o['id']!=1  and rectangle(entite).colliderect(rectangle(o)):
                    if o['id'] and o['id']!=5 and o['id']!=6 and o['id']!=7 and o['id']!=8 and o['id']!=9:
                        enleveEntite(scene, entite)
                    if o['id']==2:
                        enleveEntite(scene, o)
                        killcount+=1
                    if o['id']==3:
                        life_boss-=1
                        if life_boss==0:
                            enleveEntite(scene,o)
                    if  o['id']==2 and killcount%10==0 and killcount!=0 and mechant==False:
                        vit_zombie += 1
                    if o['id']==2 and killcount%20==0 and recal==0:
                        recal=1
                        nouveauBoss()
##### Aleatoire #####

def nouvMomentAleatoire(intervalle):
    return {
        'momentSuivant': 0,
        'max': intervalle,
        'min': intervalle//2
    }

def suivant(momentAleatoire, maintenant):
    momentAleatoire['momentSuivant'] = maintenant + random.randint(momentAleatoire['min'], momentAleatoire['max'])


def estExpire(momentAleatoire, maintenant):
    return momentAleatoire['momentSuivant']<= maintenant

##### Fin Aleatoire #####

##### Tir et Zombie #####

def nouveauTir():
    balle = nouvelleEntite()
    balle['id']=1
    ajoutePose(balle, IMAGE_BALLE)
    prendsPose(balle, 0)
    ajouteEntite(scene, balle)
    visible(balle)
    vitesse(balle, vit_balle)
    if indice==4 or indice==5:
        place(balle,perso['position'][0]+80, perso['position'][1]+65)
    elif indice==2 or indice==3:
        place(balle, perso['position'][0]+60, perso['position'][1]+29)
    else:
        place(balle, perso['position'][0]+80, perso['position'][1]+29)
    if music==True:
        bruitages.play(sons['ShotGun'])
    return balle
    

def nouveauZombie(maintenant, vit_zombie):
    if estExpire(temps_entre_zombie, maintenant):
        suivant(temps_entre_zombie, maintenant)
        zombie = nouvelleEntite()
        zombie['id']=2
        zombie['couloir']=random.randint(1,3)
        ajoutePose(zombie, IMAGE_ZOMBIE1)
        prendsPose(zombie, 0)
        ajouteEntite(scene, zombie)
        visible(zombie)
        vitesse(zombie,vit_zombie)
        couloir_zombie(zombie)
        return zombie

def balleBoss(maintenant, vit_balle_boss):
    if mechant and life!=0:
        if estExpire(temps_entre_balle, maintenant):
            suivant(temps_entre_balle, maintenant)
            bullet = nouvelleEntite()
            bullet['id']=4
            ajoutePose(bullet, IMAGE_BALLEBOSS)
            prendsPose(bullet, 0)
            ajouteEntite(scene, bullet)
            visible(bullet)
            vitesse(bullet, vit_balle_boss)
            for entite in acteurs(scene):
                if entite['id']==3:
                    place(bullet, entite['position'][0]-10, entite['position'][1]+65)
            return bullet

        
def nouveauBoss():
    global mechant,life_boss, numero_boss, temps_entre_balle
    boss = nouvelleEntite()
    life_boss=10
    mechant=True
    boss['id']=3
    boss['couloir']=2
    ajoutePose(boss, IMAGE_ZOMBIE_BOSS)
    prendsPose(boss, 0)
    ajouteEntite(scene, boss)
    visible(boss)
    vitesse(boss,vit_zombie_boss)
    couloir_zombie(boss)
    numero_boss+=1
    temps_entre_balle = nouvMomentAleatoire(INTERVALLE_BALLE-150*numero_boss)
    return boss

def viesBoss():
    if life_boss==10:
        for i in (520, 545, 570, 595, 620, 645, 670, 695, 720, 755):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==9:
        for i in (520, 545, 570, 595, 620, 645, 670, 695, 720):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==8:
        for i in (520, 545, 570, 595, 620, 645, 670, 695):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==7:
        for i in (520, 545, 570, 595, 620, 645, 670):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==6:
        for i in (520, 545, 570, 595, 620, 645):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==5:
        for i in (520, 545, 570, 595, 620):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==4:
        for i in (520, 545, 570, 595):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==3:
        for i in (520, 545, 570):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==2:
        for i in (520, 545):
            fenetre.blit(IMAGE_COEUR_VERT, (i, 20))
    if life_boss==1:
            fenetre.blit(IMAGE_COEUR_VERT, (520, 20))

def couloir_boss(maintenant):
    for entite in acteurs(scene):
        if entite['id']==3:
            if estExpire(temps_couloir_boss, maintenant):
                suivant(temps_couloir_boss, maintenant)
                entite['couloir']= random.randint(1,3)
                couloir_perso_et_boss(entite)


def couloir_zombie(entite):
    if entite['couloir']==1:
        place(entite, FENETRE_LARGEUR+10, POSITION_Y_COULOIR1)
    if entite['couloir']==2:
        place(entite, FENETRE_LARGEUR+10, POSITION_Y_COULOIR2)
    if entite['couloir']==3:
        place(entite, FENETRE_LARGEUR+10, POSITION_Y_COULOIR3)
    
##### Fin Tir et Zombie #####

##### Score #####

def score():
    affscore = 'KILLCOUNT:' + str(killcount)
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//25, True)
    marquoir = police.render(affscore, True, BLANC)
    marquoirLargeur = 80
    fenetre.blit(marquoir, ((FENETRE_LARGEUR)//2 -marquoirLargeur*2+80, 10))

def bosstime_text():
    text = 'BOSSTIME !!!'
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//25, True)
    textboss = police.render(text, True, ROUGE)
    textbossLargeur = 80
    fenetre.blit(textboss, ((FENETRE_LARGEUR//2 - textbossLargeur*2 + 80, 35)))

def bonustir_text():
    text = 'RAPID FIRE ON'
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//30, True)
    textbonus = police.render(text, True, BLEU)
    fenetre.blit(textbonus, (130, 20))

def malustir_text():
    text = 'SLOW FIRE ON'
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//30, True)
    textbonus = police.render(text, True, ROUGE)
    fenetre.blit(textbonus, (130, 20))

def speedplus_affichage():
    text = 'ZOMBIE FASTER'
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//30, True)
    textspeed = police.render(text, True, ROUGE)
    fenetre.blit(textspeed, (130,20))

def speedmoins_affichage():
    text = 'ZOMBIE SLOWER'
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//30, True)
    textspeed = police.render(text, True, BLEU)
    fenetre.blit(textspeed, (130,20))

def replay_text(x,y):
    text = 'TO RESTART'
    text2= 'PRESS "o"'
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//30, True)
    textrestart = police.render(text, True, BLANC)
    textrestart2 = police.render(text2, True, BLANC)
    fenetre.blit(textrestart, x)
    fenetre.blit(textrestart2, y)

def continuer_text(x,y):
    text = 'TO CONTINUE'
    text2= 'PRESS "p"'
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//30, True)
    textrestart = police.render(text, True, BLANC)
    textrestart2 = police.render(text2, True, BLANC)
    fenetre.blit(textrestart, x)
    fenetre.blit(textrestart2, y)

def quit_text(x,y):
    text = 'TO QUIT'
    text2 = 'PRESS "q"'
    police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//30, True)
    textquit = police.render(text, True, BLANC)
    textquit2 = police.render(text2, True, BLANC)
    fenetre.blit(textquit, x)
    fenetre.blit(textquit2, y)

def vies():
    global joue, gameover
    if life==3:
        for i in (20,50,80):
            fenetre.blit(IMAGE_COEUR, (i, 20))
    elif life==2:
        for i in (20,50):
            fenetre.blit(IMAGE_COEUR, (i, 20))  
    elif life==1:
        fenetre.blit(IMAGE_COEUR, (20, 20))
    if life <= 0:
            joue = False
            gameover = True
    
##### Fin Score #####

##### Bonus Malus #####

def bonus_malus_apparition():
    global temps_precedent
    if estExpire(temps_bonusmalus, maintenant):
        suivant(temps_bonusmalus, maintenant)
        bonus_malus()
        temps_precedent = maintenant + 5000
    if maintenant>=temps_precedent:
        for entite in acteurs(scene):
            if entite['id']==5 or entite['id']==6 or entite['id']==7 or entite['id']==8 or entite['id']==9:
                enleveEntite(scene, entite)

def bonus_malus():
    global indice_b_m
    if delai==150:
        objet=nouvelleEntite()
        if vit_zombie>5:
            indice_b_m = random.randint(1,5)
        else :
            indice_b_m = random.choice([1,3,4,5])
        if indice_b_m == 1:
            objet['id']=5
        if indice_b_m == 2:
            objet['id']=6
        if indice_b_m == 3:
            objet['id']=7
        if indice_b_m == 4:
            objet['id']=8
        if indice_b_m == 5 and life<3:
            objet['id']=9
        if objet['id']==0:
            return
        nouveauBonus_Malus(objet)
    


def nouveauBonus_Malus(objet):
    objet['couloir']=random.randint(1,3)
    if objet['id']==5:
        ajoutePose(objet, IMAGE_LUCKYBOX)
    if objet['id']==6:
        ajoutePose(objet, IMAGE_LUCKYBOX)
    if objet['id']==7:
        ajoutePose(objet, IMAGE_LUCKYBOX)
    if objet['id']==8:
        ajoutePose(objet, IMAGE_LUCKYBOX)
    if objet['id']==9:
        ajoutePose(objet, IMAGE_BONUS_COEUR)
    x = random.randint(FENETRE_LARGEUR//3, FENETRE_LARGEUR//2)
    prendsPose(objet, 0)
    ajouteEntite(scene, objet)
    visible(objet)
    couloir_bonus_malus(objet,x)

def couloir_bonus_malus(objet,x):
    if objet['couloir']==1:
        place(objet, x, POSITION_Y_COULOIR1 + 30)
    if objet['couloir']==2:
        place(objet, x, POSITION_Y_COULOIR2 + 30)
    if objet['couloir']==3:
        place(objet, x, POSITION_Y_COULOIR3 + 30)
    
##### Fin Bonus Malus #####

##### Reset Game #####

def reset_game():
    global gameover, life, killcount, vit_zombie, mechant, pause, fini, joue, life_boss, delai, numero_boss
    if gameover:
        gameover = False
    life = 3
    life_boss = 0
    killcount = 0
    vit_zombie=2
    mechant = False
    pause = False
    fini = False
    joue = False
    delai = 150
    numero_boss=0
    for entite in acteurs(scene):
        enleveEntite(scene, entite)
    place(perso, 30,POSITION_Y_COULOIR2)
    perso['vitesse']= 5
    ajouteEntite(scene, perso)
    perso['couloir']=2


##### Fin Reset Game #####
##### Conditions Boucle #####

def Cond_Anim_tir():
    global indice
    if indice == 1:
        indice = 0
    if indice == 3:
        indice = 2
    if indice == 5:
        indice = 4
        
def Cond_Stop_Anim_BM():
    global replay_time, gameover_count
    if gameover_count>=1:
        replay_time = maintenant + 5000
        gameover_count=0
    if fin_speedplus_affichage>maintenant:
        speedplus_affichage()
    if fin_speedmoins_affichage>maintenant:
        speedmoins_affichage()
        
def Cond_pause():
    global temps_precedent, fin_tir_rapide, fin_tir_lent
    if pause:
        fenetre.blit(IMAGE_PAUSE, (FENETRE_LARGEUR//2-DIMENSION_PAUSE//2, FENETRE_HAUTEUR//2-DIMENSION_PAUSE//2))
        replay_text(PAUSE_REPLAY_TEXT, PAUSE_REPLAY_TEXT2)
        continuer_text(PAUSE_CONTINUE_TEXT, PAUSE_CONTINUE_TEXT2)
        suivant(temps_bonusmalus, maintenant)
        if temps_precedent>maintenant:
            temps_precedent = temps_pause_malus+maintenant
        if maintenant<fin_tir_rapide:
            fin_tir_rapide= temps_restant+maintenant
        if maintenant<fin_tir_lent:
            fin_tir_lent= temps_restant+maintenant
    else:
        balleBoss(maintenant, vit_balle)
        
def Cond_mechant():
    global mechant, recal
    if killcount%20==0 and killcount!=0:
        mechant=True
    if life_boss==0:
        mechant = False
        recal = 0
    if mechant:
        bosstime_text()
        if not pause:
            couloir_boss(maintenant)
        viesBoss()

def Cond_mechant_pause():
    if not pause and not mechant:
        if maintenant>5000 and maintenant>=replay_time:
            bonus_malus_apparition()
        nouveauZombie(maintenant, vit_zombie)
        
def Cond_delai():
    global delai, indice
    if (fin_tir_rapide<=maintenant and fin_tir_lent<=maintenant) or gameover:
        delai=150
        indice = 0
    if delai == 50:
        bonustir_text()
    if delai ==300:
        malustir_text()

def Cond_music():
    if music==True:
        if joue:
            sons['musique'].play(loops=-1)
        if gameover:
            sons['musique'].stop()
    
    


pygame.init()
pygame.mixer.init()
pygame.key.set_repeat(200, 25)

##### Variable Music #####

music= True

##### Fin Variable Music #####

fenetre_taille = (FENETRE_LARGEUR, FENETRE_HAUTEUR)
fenetre = pygame.display.set_mode(fenetre_taille)
pygame.display.set_caption('THE MANSION')

perso = nouvelleEntite()
for nom_fichier in ('ShooterNotShoot.png','ShooterShoot2.png', 'ShooterGun.png', 'ShooterGunShoot.png', 'ShooterMiniGun.png','ShooterMiniGunShoot.png'):
    chemin = 'Images_PPI_Final/' + nom_fichier
    if nom_fichier == 'ShooterNotShoot.png':
        dimension_perso = (PERSO_LARGEUR, PERSO_HAUTEUR)
    elif nom_fichier=='ShooterGun.png' or nom_fichier=='ShooterGunShoot.png':
        dimension_perso =(PERSO_LARGEUR-3, PERSO_HAUTEUR)
    else:
        dimension_perso = (PERSO_LARGEUR+20, PERSO_HAUTEUR+5)
    perso_image = pygame.image.load(chemin).convert_alpha(fenetre)
    perso_image = pygame.transform.scale(perso_image, dimension_perso)
    ajoutePose(perso, perso_image)

scene = nouvelleScene()
ajouteEntite(scene, perso)

fenetre_taille = (FENETRE_LARGEUR, FENETRE_HAUTEUR)
fenetre = pygame.display.set_mode(fenetre_taille)
temps = pygame.time.Clock()

IMAGE_FOND = pygame.image.load('Images_PPI_Final/Fond_Hotel.png').convert_alpha(fenetre)
IMAGE_FOND = pygame.transform.scale(IMAGE_FOND, (fenetre_taille))

IMAGE_PERSO_INTRO = pygame.image.load('Images_PPI_Final/ShooterIntro.png').convert_alpha(fenetre)
IMAGE_PERSO_INTRO = pygame.transform.scale(IMAGE_PERSO_INTRO, (140, 141))

IMAGE_PERSO_MINIG = pygame.image.load('Images_PPI_Final/ShooterMiniGun.png').convert_alpha(fenetre)
IMAGE_PERSO_MINIG = pygame.transform.scale(IMAGE_PERSO_MINIG, (PERSO_LARGEUR, PERSO_HAUTEUR))

IMAGE_ZOMBIE1 = pygame.image.load('Images_PPI_Final/ZombieWalk.png').convert_alpha(fenetre)
IMAGE_ZOMBIE1 = pygame.transform.scale(IMAGE_ZOMBIE1, (ZOMBIE_LARGEUR, ZOMBIE_HAUTEUR))

IMAGE_BALLE = pygame.image.load('Images_PPI_Final/BalleNormal.png').convert_alpha(fenetre)
IMAGE_BALLE = pygame.transform.scale(IMAGE_BALLE, (BALLE_LARGEUR, BALLE_HAUTEUR))

IMAGE_BALLEBOSS = pygame.image.load('Images_PPI_Final/BalleBoss.png').convert_alpha(fenetre)
IMAGE_BALLEBOSS = pygame.transform.scale(IMAGE_BALLEBOSS, (BALLE_LARGEUR, BALLE_HAUTEUR))

IMAGE_COEUR = pygame.image.load('Images_PPI_Final/CoeurRouge.png').convert_alpha(fenetre)
IMAGE_COEUR = pygame.transform.scale(IMAGE_COEUR, (DIMENSION_COEUR,DIMENSION_COEUR))

IMAGE_COEUR_VERT = pygame.image.load('Images_PPI_Final/CoeurVert.png').convert_alpha(fenetre)
IMAGE_COEUR_VERT = pygame.transform.scale(IMAGE_COEUR_VERT, (DIMENSION_COEUR,DIMENSION_COEUR))

IMAGE_PAUSE = pygame.image.load('Images_PPI_Final/pause.png').convert_alpha(fenetre)
IMAGE_PAUSE = pygame.transform.scale(IMAGE_PAUSE, (DIMENSION_PAUSE,DIMENSION_PAUSE))

IMAGE_ZOMBIE_BOSS = pygame.image.load('Images_PPI_Final/ZombieBoss.png').convert_alpha(fenetre)
IMAGE_ZOMBIE_BOSS = pygame.transform.scale(IMAGE_ZOMBIE_BOSS, (ZOMBIE_LARGEUR,ZOMBIE_HAUTEUR))

IMAGE_ZOMBIE_INTRO = pygame.transform.scale(IMAGE_ZOMBIE1, (ZOMBIE_INTRO_LARGEUR, ZOMBIE_INTRO_HAUTEUR))

IMAGE_LUCKYBOX = pygame.image.load('Images_PPI_Final/LuckyBox.png').convert_alpha(fenetre)
IMAGE_LUCKYBOX = pygame.transform.scale(IMAGE_LUCKYBOX, (BONUS_MALUS_TAILLE))

IMAGE_MANOIR = pygame.image.load('Images_PPI_Final/Manoir.png').convert_alpha(fenetre)
IMAGE_MANOIR = pygame.transform.scale(IMAGE_MANOIR, (FENETRE_LARGEUR,FENETRE_HAUTEUR))

IMAGE_BONUS_COEUR = pygame.image.load('Images_PPI_Final/CoeurRougeBonus.png').convert_alpha(fenetre)
IMAGE_BONUS_COEUR = pygame.transform.scale(IMAGE_BONUS_COEUR, (BONUS_MALUS_TAILLE))

IMAGE_CIMETIERE = pygame.image.load('Images_PPI_Final/cimetiere.png').convert_alpha(fenetre)
IMAGE_CIMETIERE = pygame.transform.scale(IMAGE_CIMETIERE, (fenetre_taille))

police = pygame.font.SysFont('monospace', FENETRE_HAUTEUR//25, True)
police_titre = pygame.font.SysFont('monospace', 50, True)

place(perso, 30,POSITION_Y_COULOIR2)
vitesse(perso, 5)

maintenant = 0
prochain = 0
delai = 150
temps_pause_malus = 0

fin_tir_rapide=0
fin_tir_lent=0
fin_speedplus_affichage=0
fin_speedmoins_affichage=0
temps_restant=0

temps_precedent = 0
vit_zombie = 2
vit_balle = 10
vit_balle_boss = -10
vit_zombie_boss = 1
numero_boss=0
gameover_count = 0

temps_entre_balle=0
temps_entre_zombie = nouvMomentAleatoire(INTERVALLE_ZOMBIE)
temps_couloir_boss = nouvMomentAleatoire(INTERVALLE_COULOIR_BOSS)
temps_bonusmalus = nouvMomentAleatoire(INTERVALLE_BONUSMALUS)

if music==True:
    sons = {}
    sons['musique'] = pygame.mixer.Sound("Musique_PPI/Musique_horreur.wav")
    sons['ShotGun'] = pygame.mixer.Sound("Musique_PPI/Shot_gun.wav")
    bruitages = pygame.mixer.Channel(2)

killcount = 0
indice = 0

life = 3
life_boss = 10

replay_time = 0
numero_boss=0
recal=0
pause = False
fini = False
joue = False
gameover = False
mechant = False
write = True

while not fini:

    dessine_intro()
    traite_entrees()

    pygame.display.flip()
    temps.tick(60)
    while joue:
        maintenant = pygame.time.get_ticks()
        
        Cond_music()
        Cond_Anim_tir()
        
        dessine_court()
        traite_entrees()
        couloir_perso_et_boss(perso)
        prendsPose(perso, indice)
        limite_horiz()
        limite_entite()
        score()
        vies()
        collision()
        miseAJour(scene)
        affiche(scene, fenetre)
        
        Cond_pause()
        Cond_mechant()
        Cond_mechant_pause()
        Cond_delai()
        Cond_Stop_Anim_BM()

        pygame.event.pump()          
        pygame.display.flip()
        temps.tick(60)
    
    while gameover:
        Cond_music()
        dessine_fin()
        replay_text(GAMEOVER_REPLAY_TEXT, GAMEOVER_REPLAY_TEXT2)
        quit_text( GAMEOVER_QUIT_TEXT, GAMEOVER_QUIT_TEXT2)
        gameover_count=+1
        traite_entrees_gameover()
        pygame.event.pump()          
        pygame.display.flip()
        temps.tick(60)

pygame.display.quit()
exit()