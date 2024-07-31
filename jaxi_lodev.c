// Form ray cast from player into scene
vRayStart = vPlayer 
olc::vf2d vRayDir = (vMouseCell - vPlayer).norm();

//scaling factor that links our hypotenuse to a step change of unit direction 
RayUnitStepSize = deltaDist
vRayUnitStepSize = { abs(1.0f / vRayDir.x), abs(1.0f / vRayDir.y) };
deltaDist = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);

vRayLength1D = sideDist
vRayLength1D.x = (vRayStart.x - float(vMapCheck.x)) * vRayUnitStepSize.x;

if rayDirY < 0
    stepY = +1

vMapCheck = mapX
vMapCheck = vRayStart;
mapX = (int)posX;

vRayLength1D = sideDistX

bTileFound = hit

vIntersection: ponto de colisao