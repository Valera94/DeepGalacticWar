# DeepGalacticWar
A universe that will force everyone to take part in a large-scale war.

# Project version v.1 :

You can show or download project :
https://youtu.be/IMgqBSFB1vo/, https://valera94.itch.io/pet-project-battlefield-aimultiplayer/.

*The framework was used* __Blueprint/C++__ :
- Core Framework UnrealEngine (GameMode|GameState|HUD etc...)
- [UMG/Slate UI/UX](#ui-ux)
- EnhancedInputComponent
- [Gameplay Ability System](#gas-system)
- Niagara|Particle
- [Animation Blueprint](#animation-blueprint)
- [Artificial Intelligence](#artificial-intelligence)
- etc...


*In the current version of the project* v.1:
> *В текущей версии проекта* v.1:
- Default base cycle widget.
- > стандартный жизненный цикл.
- Game mode Command Battle.
- > игровой режим коммандный бой.
- It has basic standard UI sets without images and animations, where it is possible to miss it and where there is no complete functionality.
- > Имеет базовые стандартные наборы UI без изображения и анимаций, где это возможно упустить и где нет законченного функционала.
- Implemented a map with the IDs of the current players on them.
- > Реализована карта с идентификаторами действующих игроков на них.
- The GAS System is connected
- > Подключена GAS System 



# UI UX
### V.1
![image](https://github.com/Valera94/DeepGalacticWar/assets/91465697/14d0d7d0-7c84-4130-a9d6-bfbc70cb16c6)

- The game has four "layerwidgets" for the character, which display common and unique information.
- >В игре присутствует четыре "LayerWidget" для персонажа, которые отображают общую и уникальную информацию.
 - Layer Map
 - Layer Pawn
 - Layer Death
 - Layer waitDeploy

Depending on the status or button click, we can switch to a specific "Layers".
The common widgets were saved as a reference in the main HUD and, depending on the current state of the Layers, we simply insert them into another container and get all the same information, without any need to create and initialize the data.
>В зависимости от статуса или нажатия кнопки, мы можем переключаться на определенный "Layers".
>Общие виджеты, были сохранены ввиде референса в главном HUD и в зависимости от текущего состояния Layers, мы просто подставляем в дургой контейнер и получаем все ту же информацию, без какой либо необходимости заного создавать и инициализировать данные.


![image](https://github.com/Valera94/DeepGalacticWar/assets/91465697/bcf07851-46b0-416b-9592-ecd60bc78cf8)

- A minimap has been created, It does not use the camera's Render, but is a picture taken at 15000-15000 pixels and mathematically calculated for complete correctness in the world.
- >Создана миникарта, Она не использует Render от камеры, а является картинкой, снятой в 15000-15000 пиксель и математически рассчитана для полной корректности в мире. 


# GAS System
### V.1

Базовые атрибуты:
- Health
Базовые способности:
- Jump
- Aim
- Reload
- Sprint
- Shot
GameplayCue
- Shoot

  Данные реализации можно посотреть в С++ проекте.

# Animation Blueprint
### V.1
   ![image](https://github.com/Valera94/DeepGalacticWar/assets/91465697/de81574b-be87-4d22-8783-1d06d92aa28c)

- We use not only Animation and Montage, but also AdditiveRuntimeBone as an implementation of aiming, which transmits its data through the "AC_CharMove" component
- >Используем не только Animation и Montage но и используем AdditiveRuntimeBone в качестве реализации прицеливания, который передаетс свои данные через компонент "AC_CharMove"
  
- Реализованы: 
  - BlendSpace. 
  - TypeAnimation Run/Walk/Crouch. 
  - BlendPose UpperBone Aim. 


# Artificial Intelligence
### V.1
![image](https://github.com/Valera94/DeepGalacticWar/assets/91465697/c45bc061-a0a0-4a9c-87a8-954156ae87fb)

At the moment, we have the simplest possible AI implementation, only basic primitive tasks have been done. You can see the three final stages:
>На текущий момент, мы имеем максимальное простую реалзиацю AI, сделаны только базовые примитивные задачи. Вы можете видеть, три конечные стадии:

- Capture BasePoint.
- Fight.
- Wait Respawn.

We use only one signal, we see or do not see the enemy. All the years speak for themselves and don't make sense to explain.
>Мы используем только один сигнал, видим или не видим противника. Все ноды говорят сами за себя и не имеют смысла в объяснении.



