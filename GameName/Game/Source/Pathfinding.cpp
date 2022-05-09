#include "App.h"
#include "PathFinding.h"
#include "Render.h"
#include "Map.h"
#include "Entities.h"
#include "Defs.h"
#include "Log.h"

PathFinding::PathFinding(bool isActive) : Module(isActive), map(NULL), lastPath(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.Create("pathfinding");
	toSave = false;
}

// Destructor
PathFinding::~PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	lastPath.Clear();
	RELEASE_ARRAY(map);

	return true;
}

// Sets up the walkability map
void PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
			pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

bool PathFinding::IsTileEmpty(const iPoint& pos) const
{
	for (int i = 0; i < app->entities->entities.count(); i++)
	{
		Entity* p;
		app->entities->entities.at(i, p);
		if (pos == p->tilePos)
		{
			return false;
		}
	}

	return true;
}

bool PathFinding::ReadPattern( iPoint center, iPoint pattern[])
{

	ResetBFSPath();
	InitBFS(center);

	iPoint attackTile;

	for (int i = 0; i < 20; i++)
	{
	
		attackTile.x = center.x + pattern[i].x;
		attackTile.y = center.y + pattern[i].y;
		visited.add(attackTile);
		
	}



	return false;
}


// Utility: return the walkability value of a tile
uchar PathFinding::GetTileAt(const iPoint& pos) const
{
	if(CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

void PathFinding::DrawPath()
{
	if (DEBUG)
	{
		const DynArray<iPoint>* path = GetLastPath();
		SDL_Rect rect;

		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			rect.x = pos.x;
			rect.y = pos.y;
			rect.w = 16;
			rect.h = 16;
			app->render->DrawRectangle(rect, 255, 125, 0, 150);
		}
	}
}

// To request all tiles involved in the last generated path
const DynArray<iPoint>* PathFinding::GetLastPath() const
{
	return &lastPath;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
p2ListItem<PathNode>* PathList::Find(const iPoint& point) const
{
	p2ListItem<PathNode>* item = list.start;
	while(item)
	{
		if(item->data.pos == point)
			return item;
		item = item->next;
	}
	return item;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
p2ListItem<PathNode>* PathList::GetNodeLowestScore() const
{
	p2ListItem<PathNode>* ret = NULL;
	int min = 65535;

	p2ListItem<PathNode>* item = list.end;
	while(item)
	{
		if(item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& listToFill, PathFinding* path) const
{
	iPoint cell;
	uint before = listToFill.list.count();

	// north
	cell.Create(pos.x, pos.y + 1);
	if(path->IsWalkable(cell))
		listToFill.list.add(PathNode(-1, -1, cell, this));

	// south
	cell.Create(pos.x, pos.y - 1);
	if(path->IsWalkable(cell))
		listToFill.list.add(PathNode(-1, -1, cell, this));

	// east
	cell.Create(pos.x + 1, pos.y);
	if(path->IsWalkable(cell))
		listToFill.list.add(PathNode(-1, -1, cell, this));

	// west
	cell.Create(pos.x - 1, pos.y);
	if(path->IsWalkable(cell))
		listToFill.list.add(PathNode(-1, -1, cell, this));

	return listToFill.list.count();
}

uint PathNode::FindVisitedAdjacents(PathList& listToFill, PathFinding* path) const
{
	iPoint cell;
	uint before = listToFill.list.count();

	// north
	cell.Create(pos.x, pos.y + 1);
	if (path->IsVisited(cell))
		listToFill.list.add(PathNode(-1, -1, cell, this));

	// south
	cell.Create(pos.x, pos.y - 1);
	if (path->IsVisited(cell))
		listToFill.list.add(PathNode(-1, -1, cell, this));

	// east
	cell.Create(pos.x + 1, pos.y);
	if (path->IsVisited(cell))
		listToFill.list.add(PathNode(-1, -1, cell, this));

	// west
	cell.Create(pos.x - 1, pos.y);
	if (path->IsVisited(cell))
		listToFill.list.add(PathNode(-1, -1, cell, this));

	return listToFill.list.count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{

	int ret = -1;

	PathList open;
	PathList close;
	PathList adjacents;

	PathNode nodeStart(0, 0, origin, nullptr);

	open.list.add(nodeStart);

	p2ListItem<PathNode>* current = open.list.start;
	p2ListItem<PathNode>* lowest;
	lastPath.Clear();

	if (IsWalkable(origin) && IsWalkable(destination))
	{
		while (open.list.count() > 0)
		{

			lowest = open.GetNodeLowestScore();
			current = close.list.add(lowest->data);
			open.list.del(lowest);

			if (current->data.pos == destination)
			{
				lastPath.Clear();
				// backtrack the path
				const PathNode* lastItem = &current->data;
				while (lastItem)
				{
					lastPath.PushBack(lastItem->pos);

					lastItem = lastItem->parent;
				}
				lastPath.Flip();
				ret = lastPath.Count();
				break;
			}

			current->data.FindWalkableAdjacents(adjacents, this);

			p2ListItem<PathNode>* adj = adjacents.list.start;
			while (adj != NULL)
			{
				if (close.Find(adj->data.pos) != NULL)
				{
					adj = adj->next;
					continue;
				}

				p2ListItem<PathNode>* adjacentInOpen = open.Find(adj->data.pos);

				if (adjacentInOpen == NULL)
				{
					adj->data.CalculateF(destination);
					open.list.add(adj->data);
				}
				else {

					if (adjacentInOpen->data.g > (adj->data.g + 1))
					{
						adjacentInOpen->data.parent = adj->data.parent;
						adjacentInOpen->data.CalculateF(destination);
					}
				}
				adj = adj->next;
			}
		}
	}
	return ret;
}

int PathFinding::CreateVisitedPath(const iPoint& origin, const iPoint& destination)
{
	int ret = -1;

	PathList open;
	PathList close;
	PathList adjacents;

	PathNode nodeStart(0, 0, origin, nullptr);

	open.list.add(nodeStart);

	p2ListItem<PathNode>* current = open.list.start;
	p2ListItem<PathNode>* lowest;
	lastPath.Clear();

	if (IsVisited(origin) && IsVisited(destination))
	{
		while (open.list.count() > 0)
		{

			lowest = open.GetNodeLowestScore();
			current = close.list.add(lowest->data);
			open.list.del(lowest);

			if (current->data.pos == destination)
			{
				lastPath.Clear();
				// backtrack the path
				const PathNode* lastItem = &current->data;

				//check that the last node is empty,
				//if not last item is parent item
				if (!IsTileEmpty(lastItem->pos))
					lastItem = lastItem->parent;

				while (lastItem)
				{
					lastPath.PushBack(lastItem->pos);

					lastItem = lastItem->parent;
				}

				lastPath.Flip();
				ret = lastPath.Count();
				break;
			}

			current->data.FindVisitedAdjacents(adjacents, this);

			p2ListItem<PathNode>* adj = adjacents.list.start;
			while (adj != NULL)
			{
				if (close.Find(adj->data.pos) != NULL)
				{
					adj = adj->next;
					continue;
				}

				p2ListItem<PathNode>* adjacentInOpen = open.Find(adj->data.pos);

				if (adjacentInOpen == NULL)
				{
					adj->data.CalculateF(destination);
					open.list.add(adj->data);
				}
				else {

					if (adjacentInOpen->data.g > (adj->data.g + 1))
					{
						adjacentInOpen->data.parent = adj->data.parent;
						adjacentInOpen->data.CalculateF(destination);
					}
				}
				adj = adj->next;
			}
		}
	}
	return ret;
}

// ----------------------------------------------------------------------------------
// Actual BFS algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------

void PathFinding::PropagateBFS()
{
	iPoint current;
	if (frontier.Pop(current)) {

		p2List<iPoint> neightbours;

		neightbours.add(iPoint(current.x + 1, current.y));
		neightbours.add(iPoint(current.x, current.y + 1));
		neightbours.add(iPoint(current.x, current.y - 1));
		neightbours.add(iPoint(current.x - 1, current.y));

		p2ListItem<iPoint>* neightbour = neightbours.start;
		while (neightbour != NULL)
		{
			if (visited.find(neightbour->data) == false &&	IsWalkable(neightbour->data))
			{
				frontier.Push(neightbour->data);
				visited.add(neightbour->data);
			}
			neightbour = neightbour->next;
		}
	}
}


void PathFinding::GenerateWalkeableArea(iPoint center, int range)
{
	ResetBFSPath();
	InitBFS(center);

	for (int x = center.x - range; x < center.x + range; x++)
		for (int y = center.y - range; y < center.y + range; y++)
		{
			iPoint next;
			next.x = x;
			next.y = y;
						
			if (!visited.find(next) && IsWalkable(next) 
				&& IsTileEmpty(next)&& CreatePath(center,next) <= range)
			{
				//frontier.Push(next);								
				visited.add(next);
			}
		}

	lastPath.Clear();
}

void PathFinding::GenerateInteractionArea(iPoint center, int range)
{
	ResetBFSPath();
	InitBFS(center);

	for (int x = center.x - range; x < center.x + range; x++)
		for (int y = center.y - range; y < center.y + range; y++)
		{
			iPoint next;
			next.x = x;
			next.y = y;

			if (!visited.find(next) && IsWalkable(next)
				 && CreatePath(center, next) <= range)
			{					
				visited.add(next);
			}
		}

	lastPath.Clear();
}

//Reset bfs expanison
void PathFinding::ResetBFSPath()
{
	frontier.Clear();
	visited.clear();
}

void PathFinding::InitBFS(iPoint pos)
{
	frontier.Push(pos);
	visited.add(pos);
}

void PathFinding::DrawBFSPath()
{
	iPoint point;

	// Draw visited
	p2ListItem<iPoint>* item = visited.start;
	SDL_Rect rect;
	while (item != nullptr)
	{
		point = item->data;

		iPoint pos = app->map->MapToWorld(point.x, point.y);
		rect.x = pos.x;
		rect.y = pos.y;
		rect.w = (app->map->mapData.tileWidth);
		rect.h = (app->map->mapData.tileHeight);
		app->render->DrawRectangle(rect, 100, 50, 100, 125);

		item = item->next;
	}

	// Draw frontier
	for (uint i = 0; i < frontier.Count(); ++i)
	{
		point = *(frontier.Peek(i));
		rect.x = point.x;
		rect.y = point.y;
		rect.w = (app->map->mapData.tileWidth);
		rect.h = (app->map->mapData.tileHeight);
		app->render->DrawRectangle(rect, 100, 0, 155, 100);
	}

}


bool PathFinding::IsVisited(const iPoint& pos) const
{
	p2ListItem<iPoint>* p = visited.start;

	while (p != NULL)
	{
		if (p->data == pos)
			return true;

		p = p->next;
	}

	return false;
}
