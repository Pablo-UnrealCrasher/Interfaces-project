# Interfaces-project

## Controls
- WASD - Movement
- Space - Jump
- Left-Click (While holding a Gun) - Shoot
- Hold Left-Click (Inside the Upgrade Menu) - Upgrade Skill
- Right-Click (Hold) - Grab Objects
- Left-Shift - Open Upgrade Menu

## How to Play
Go on top of a gun to pick it up. The enemies cannot kill the player but will run towards them.
Gain Points by destroying Breakable Statues (The Object right next to the guns is one).
You can upgrade your skills by using those points.

## Where the project comes from
I started this project using a previous project for my Physics Class as a base. Every User Interface implementation made for the Upgrade Menu has been made from scratch and stored in a separate C++ folder (InterfacesScripts).

## How the project was structured
The project has been built using Custom User Widgets defined in C++ as its base. All of the User Widgets' interactive elements are bound to their C++ script using the BindWidget decorator to ensure ease of use on the Blueprint side of things. 

The Custom User Widgets were also made to be reusable across instances: For example, the UpgradeButton exposes a Texture2D parameter ("UpgradeIcon") and, when altered, inmmediatly applies the new value to its styles using the SynchronizeProperties() overriden function.

To avoid unnecessary interdependencies, the Custom User Widgets use Dynamic Delegates extensively. This way, only higher order User Widgets (those that contain other user widgets) have a reference to their child, and never the other way around.

In the case of temporary messages or visuals, Timer Delegates have been used to temporarily enable and then disable the visibility of UI elements. Similarly, when a UI menu had to be disabled, its Visibility was affected, instead of Destroying and recreating the widget, which had the risk of been performance intensive.

Finally, in the case of the custom UpgradeButton, a small trick was used to simplified its logic: When the button is "locked" because the player has not unlocked the previous upgrade yet, the button is technically still interactible. However, we don't allow that interaction by placing a "locked" image on top of it and making that Hit-Testable.