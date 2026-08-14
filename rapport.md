# GPA434 — Ingénierie des systèmes orientés-objet

## Laboratoire 3 — Application graphique liée à l'évolution différentielle

Équipe :

- Frederic Tchouanguep (TCHF12028409)
- Ahmed Sadek (SADA63290301)
- Paul Ayoub (AYOP28099900)

Date : 2026/08/13

---

# Problème 1 — Optimisation géométrique

## Diagramme de classes UML

```plantuml
@startuml
skinparam classAttributeIconSize 0
left to right direction

abstract class QDESolutionPanel {
  +{abstract} buildSolution() : de::SolutionStrategy*
  +updateVisualization(adapter)
  +parameterChanged() <<signal>>
}

abstract class "de::SolutionStrategy" as SolutionStrategy {
  #mSolutionDomain
  +{abstract} toString(solution) : string
  +engineParameters() : EngineParameters
  #{abstract} process(solution) : double
}

abstract class PolygonBuilder {
  +{abstract} name() : QString
  +{abstract} createPolygon() : QPolygonF
}

class TriangleBuilder {
  +name() : QString
  +createPolygon() : QPolygonF
}

class RectangleBuilder {
  +name() : QString
  +createPolygon() : QPolygonF
}

class LShapeBuilder {
  +name() : QString
  +createPolygon() : QPolygonF
}

class QDEGeometricPanel {
  -mVisualizationLabel : QImageViewer*
  -mShapeComboBox : QComboBox*
  -mObstacleSpinBox : QSpinBox*
  -mRegenerateButton : QPushButton*
  -mCanvasSize : QSizeF
  -mObstacles : vector<QPointF>
  -mPolygonBuilders : vector<unique_ptr<PolygonBuilder>>
  +buildSolution() : de::SolutionStrategy*
  +updateVisualization(adapter)
  -shapeSelectionChanged()
  -regenerateObstacles()
  -selectedBuilder() : PolygonBuilder&
  -selectedPolygon() : QPolygonF
  -drawVisualization(population)
}

class "QDEGeometricPanel::GeometricStrategy" as GeometricStrategy {
  -mCanvasSize : QSizeF
  -mObstacles : vector<QPointF>
  -mBasePolygon : QPolygonF
  -mBaseArea : double
  +toString(solution) : string
  +engineParameters() : EngineParameters
  +{static} transformPolygon(polygon, solution) : QPolygonF
  #process(solution) : double
  -isValid(polygon) : bool
  -isStrictlyInside(point, polygon) : bool
  -isOnBoundary(point, polygon) : bool
  -{static} polygonArea(polygon) : double
  -{static} polygonDiameter(polygon) : double
}

class QDEAdapter

QDEGeometricPanel --|> QDESolutionPanel
GeometricStrategy --|> SolutionStrategy
TriangleBuilder --|> PolygonBuilder
RectangleBuilder --|> PolygonBuilder
LShapeBuilder --|> PolygonBuilder

QDEGeometricPanel *-- "3" PolygonBuilder
QDEGeometricPanel ..> GeometricStrategy : crée (buildSolution)
QDEGeometricPanel ..> QDEAdapter : visualise

note bottom of PolygonBuilder : Approche polymorphique créée pour ce problème :\nle panneau manipule les formes uniquement via cette interface.
@enduml
```

Le panneau possède les trois créateurs par `std::unique_ptr<PolygonBuilder>`. La sélection d'une forme utilise donc réellement l'interface abstraite, sans logique géométrique dans le panneau.

## Domaine et fonction objective

Une solution contient quatre valeurs :

| Indice | Valeur | Domaine |
|---:|---|---|
| 0 | Position `x` | `[0, largeur]` |
| 1 | Position `y` | `[0, hauteur]` |
| 2 | Rotation | `[0°, 360°]` |
| 3 | Échelle | `[0, diagonale du canevas / diamètre du polygone]` |

La borne d'échelle est sûre : une forme dont le diamètre dépasse la diagonale du canevas ne peut pas y entrer. La transformation applique l'échelle, la rotation, puis la translation avec `QTransform`.

Une solution est invalide si son rectangle englobant sort du canevas ou si un obstacle est strictement à l'intérieur du polygone. Le contact avec le canevas ou un obstacle reste permis. Un test séparé du contour, avec une petite tolérance, évite de rejeter ces contacts.

La fonction objective à maximiser est directe :

```text
solution valide   : aireInitiale × échelle²
solution invalide : 0
```

La stratégie utilise `de::OptimizationMaximization` et `de::FitnessIdentity`, comme le problème de la boîte ouverte.

Les paramètres recommandés sont une population de `60` solutions et `400` générations, ce qui reste raisonnable pour un problème à quatre dimensions. Le facteur de mutation `f = 0.25` et le taux de croisement `R = 0.75` sont ceux qui ont donné la meilleure convergence lors de nos essais.

---

# Problème 2 — Visage souriant (sujet ouvert)

## Présentation technique du problème

Le problème consiste à retrouver, par évolution différentielle, les paramètres
d'un visage souriant correspondant exactement à un visage de référence affiché
à l'écran. Le visage est décrit par quatre traits paramétriques :

- la tête, un cercle (centre `x`, `y` et rayon `r`);
- l'œil gauche et l'œil droit, deux cercles indépendants (`x`, `y`, `r` chacun);
- la bouche, une branche d'hyperbole centrée sur son sommet
  `y(x) = k − a·(√(1 + ((x − h) / b)²) − 1)`, définie par sa position (`h`, `k`),
  sa courbure `a`, son ouverture `b` et sa largeur échantillonnée `w`.

Une solution regroupe donc `3 × 3 + 5 = 14` valeurs réelles. L'algorithme ne
voit jamais le dessin : il ne manipule que ces 14 nombres. La correspondance
visuelle émerge de la fonction objective.

Intrants (fixés avant la résolution, six éléments de paramétrisation) :

| Élément | Rôle |
|---|---|
| Rayon de la tête | Taille du visage de référence |
| Rayon des yeux | Taille des yeux de référence |
| Écartement des yeux | Distance entre les deux yeux |
| Courbure de la bouche | Paramètre `a` de l'hyperbole de référence |
| Largeur de la bouche | Paramètre `w` de l'hyperbole de référence |
| Ouverture de la bouche | Paramètre `b` de l'hyperbole de référence |

Les six éléments décrivent tous le visage de référence : chaque dimension de
la solution correspond ainsi à une valeur que l'usager peut réellement
influencer. Le nombre de points comparés par trait est une constante du
panneau. Un bouton `Régénérer un visage` tire aléatoirement les six éléments,
produisant un nouveau visage de référence à retrouver.

Extrants :

- la meilleure solution : les 14 paramètres reconstruits, présentés avec
  l'erreur totale et l'erreur par trait (`toString`);
- la visualisation : le visage de référence à gauche, toute la population à
  droite (rognée aux limites de son canevas), la meilleure solution mise en
  évidence, ainsi qu'une ligne d'information sous le canevas de droite donnant
  l'erreur totale de la meilleure solution et la génération courante.

## Domaine et fonction objective

Une solution contient quatorze valeurs :

| Indices | Trait | Valeurs | Domaine |
|---:|---|---|---|
| 0 – 2 | Tête | `x`, `y`, `r` | `[0, 400]`, `[0, 400]`, `[10, 200]` |
| 3 – 5 | Œil gauche | `x`, `y`, `r` | `[0, 400]`, `[0, 400]`, `[2, 60]` |
| 6 – 8 | Œil droit | `x`, `y`, `r` | `[0, 400]`, `[0, 400]`, `[2, 60]` |
| 9 – 13 | Bouche | `h`, `k`, `a`, `b`, `w` | `[0, 400]`, `[0, 400]`, `[1, 100]`, `[5, 200]`, `[20, 300]` |

Justification du domaine : les positions couvrent exactement le canevas de
`400 × 400`. Les bornes des rayons et des paramètres de la bouche englobent
toutes les valeurs que le panneau peut donner au visage de référence (avec une
marge), tout en excluant les cas dégénérés (rayon nul, ouverture nulle).

La fonction objective échantillonne `n` points sur chaque trait, dans le même
ordre pour le candidat et pour la référence, puis calcule :

```text
erreur(s) = somme sur les 4 traits de :
    (1/n) · somme des ||point_i(candidat) − point_i(référence)||²
```

C'est une **minimisation** (`de::OptimizationMinimization`,
`de::FitnessIdentity`) : une erreur nulle signifie que le candidat reproduit
exactement la référence. Justifications :

- la distance quadratique pénalise fortement les traits éloignés et produit un
  gradient de recherche régulier vers la référence;
- la moyenne par trait rend l'erreur indépendante du nombre de points
  d'échantillonnage (une constante du panneau, fixée à 32);
- l'échantillonnage dans un ordre déterministe (angle initial fixe pour les
  cercles, balayage gauche-droite pour la bouche) garantit que deux traits
  identiques donnent une erreur exactement nulle;
- une solution hors domaine reçoit une erreur constante très élevée.

Les paramètres recommandés sont une population de `100` solutions et `800`
générations : l'espace à quatorze dimensions est nettement plus vaste que
celui des problèmes précédents. Le facteur de mutation `f = 0.35` et le taux
de croisement `R = 0.80` sont ceux qui ont donné la meilleure convergence lors
de nos essais.

## Diagramme de cas d'utilisation UML

```plantuml
@startuml
left to right direction
actor Utilisateur

rectangle "Differential Evolution Solver — Visage souriant" {
  usecase "Configurer le visage de référence\n(6 barres de défilement)" as UC1
  usecase "Régénérer un visage aléatoire" as UC2
  usecase "Configurer l'engin d'évolution" as UC4
  usecase "Lancer / arrêter l'évolution" as UC5
  usecase "Suivre la population\net la meilleure solution" as UC6
  usecase "Consulter la description\ndu problème (Détails)" as UC7
}

Utilisateur --> UC1
Utilisateur --> UC2
Utilisateur --> UC4
Utilisateur --> UC5
Utilisateur --> UC6
Utilisateur --> UC7

UC2 ..> UC1 : <<extend>>
@enduml
```

## Diagramme de classes UML

```plantuml
@startuml
skinparam classAttributeIconSize 0

abstract class "de::SolutionStrategy" as SolutionStrategy {
  #mSolutionDomain
  +{abstract} toString(solution) : string
  +engineParameters() : EngineParameters
  #{abstract} process(solution) : double
}

abstract class QDESolutionPanel {
  +{abstract} buildSolution() : de::SolutionStrategy*
  +updateVisualization(adapter)
  +parameterChanged() <<signal>>
}

abstract class FaceShape {
  -mName : QString
  +name() : QString
  +{abstract} samplePoints(sampleCount) : QPolygonF
  +{abstract} draw(painter, sampleCount)
}

class CircleShape {
  -mCenterX : double
  -mCenterY : double
  -mRadius : double
  +samplePoints(sampleCount) : QPolygonF
  +draw(painter, sampleCount)
}

class HyperbolaShape {
  -mCenterX : double
  -mCenterY : double
  -mCurvature : double
  -mOpening : double
  -mWidth : double
  +samplePoints(sampleCount) : QPolygonF
  +draw(painter, sampleCount)
}

class QDESmileyPanel {
  -mVisualizationLabel : QImageViewer*
  -m...ScrollBar : QScrollBar* (x6)
  -mRandomizeButton : QPushButton*
  +buildSolution() : de::SolutionStrategy*
  +updateVisualization(adapter)
  -referenceChanged()
  -randomizeReference()
  -referenceParameters() : vector<double>
  -buildScrollBarLayout(scrollBar, min, max, défaut) : QHBoxLayout*
  -drawVisualization(population, génération)
  -{static} buildFaceShapes(parameters)
  -{static} drawFace(painter, parameters, sampleCount)
  -{static} randomizeScrollBar(scrollBar)
}

class "QDESmileyPanel::SmileyStrategy" as SmileyStrategy {
  -mSampleCount : int
  -mReferencePoints : vector<QPolygonF>
  -mShapeNames : vector<QString>
  +toString(solution) : string
  +engineParameters() : EngineParameters
  +{static} solutionParameters(solution) : vector<double>
  +{static} shapeError(candidat, référence) : double
  #process(solution) : double
  -shapeErrors(solution) : vector<double>
}

QDESmileyPanel --|> QDESolutionPanel
SmileyStrategy --|> SolutionStrategy
CircleShape --|> FaceShape
HyperbolaShape --|> FaceShape

QDESmileyPanel ..> SmileyStrategy : crée (buildSolution)
QDESmileyPanel ..> FaceShape : construit (1 tête, 2 yeux, 1 bouche)
SmileyStrategy ..> FaceShape : échantillonne et évalue

note bottom of FaceShape : Approche polymorphique créée pour ce problème :\nsamplePoints sert la fonction objective, draw sert la visualisation.
@enduml
```
