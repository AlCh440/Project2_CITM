#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#include "Module.h"
#include "Point.h"
#include "DynArray.h"
#include "p2List.h"
#include "Queue.h"

#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 255
#define MAX_AREA_EXPANSION 100

enum AttackShape {
	SQUARE,
	X
};

// --------------------------------------------------
// Recommended reading:
// Intro: http://www.raywenderlich.com/4946/introduction-to-a-pathfinding
// Details: http://theory.stanford.edu/~amitp/GameProgramming/
// --------------------------------------------------

class PathFinding : public Module
{
public:

	PathFinding(bool isActive);

	// Destructor
	~PathFinding();

	// Called before quitting
	bool CleanUp();

	// Sets up the walkability map
	void SetMap(uint width, uint height, uchar* data);

	// Main function to request a path from A to B
	int CreatePath(const iPoint& origin, const iPoint& destination);
	// Function to request path from A to B but visited tiles only
	int CreateVisitedPath(const iPoint& origin, const iPoint& destination);
	// Function to request path from A to B but visited, walkeable and empty tiles only
	int CreateCompletePath(const iPoint& origin, const iPoint& destination);
	//Generate BFS expansion of walkeable tiles
	void PropagateBFS();

	void ResetBFSPath();

	void InitBFS(iPoint pos);

	void GenerateWalkeableArea(iPoint center, int range);

	void GenerateInteractionArea(iPoint center, int range);

	void DrawBFSPath();

	bool IsVisited(const iPoint& pos) const;

	// To request all tiles involved in the last generated path
	const DynArray<iPoint>* GetLastPath() const;

	// Utility: return true if pos is inside the map boundaries
	bool CheckBoundaries(const iPoint& pos) const;

	// Utility: returns true is the tile is walkable
	bool IsWalkable(const iPoint& pos) const;

	//Check if any entity is in the tile
	bool IsTileEmpty(const iPoint& pos) const;

	// Utility: return the walkability value of a tile
	uchar GetTileAt(const iPoint& pos) const;

	//clear last path
	void ClearPath();

	// draw
	void DrawPath();

	bool ReadPattern(iPoint center, iPoint pattern[]);

	DynArray<iPoint> lastPath;

private:

	// size of the map
	uint width;
	uint height;

	// all map walkability values [0..255]
	uchar* map;

	//BFS Pathfinding variables
	Queue<iPoint> frontier;
	p2List<iPoint> visited;

//	SDL_Texture* tileX = nullptr;
	
};

// forward declaration
struct PathList;

// ---------------------------------------------------------------------
// Pathnode: Helper struct to represent a node in the path creation
// ---------------------------------------------------------------------
struct PathNode
{
	int g;//acumulated cost
	int h;// distance
	iPoint pos;
	const PathNode* parent; // needed to reconstruct the path in the end
	//PathFinding pathEntity; // current PathFinding

	// Convenient constructors
	PathNode();
	PathNode(int g, int h, const iPoint& pos, const PathNode* parent);
	PathNode(const PathNode& node);

	// Fills a list (PathList) of all valid adjacent pathnodes
	uint FindWalkableAdjacents(PathList& list_to_fill,PathFinding* path) const;
	uint FindVisitedAdjacents(PathList& list_to_fill,PathFinding* path) const;
	uint FindAdjacents(PathList& list_to_fill,PathFinding* path) const;
	// Calculates this tile score
	int Score() const;
	// Calculate the F for a specific destination tile
	int CalculateF(const iPoint& destination);
};

// ---------------------------------------------------------------------
// Helper struct to include a list of path nodes
// ---------------------------------------------------------------------
struct PathList
{
	// Looks for a node in this list and returns it's list node or NULL
	p2ListItem<PathNode>* Find(const iPoint& point) const;

	// Returns the Pathnode with lowest score in this list or NULL if empty
	p2ListItem<PathNode>* GetNodeLowestScore() const;

	// The list itself, note they are not pointers!
	p2List<PathNode> list;
};

#endif // __PATHFINDING_H__