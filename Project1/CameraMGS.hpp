#include "Grid.hpp"

#include "SelectorNode.hpp"
#include "BehaviorNode.hpp"
#include "RotateCamera.hpp"
#include "SequencePatrouille.hpp"
#include "SequenceAlerte.hpp"
#include "ConditionAlerte.hpp"
#include "AlerteAll.hpp"

using namespace std;
using namespace sf;

class CameraMGS {
public:

	CameraMGS(Vector2f spawnPos, float minAngle, float maxAngle);
	~CameraMGS();

	void update(float deltaTime, Grid& grid);
	void initTree(Grid& grid, EnemyManager& manager, Player& player);

	void Rotate(float deltaTime);
	void draw(RenderWindow& window);
	void rayCasting(Grid& grid);

	ConvexShape getVision();

	void setDrawable(bool value);

private:

	RectangleShape m_shape;
	ConvexShape m_vision;

	float m_minAngle;
	float m_maxAngle;
	float m_currentAngle;

	bool m_reverseSwing = false;
	bool isDrawable = true;

	unique_ptr<SelectorNode> m_root;

	unique_ptr<SequencePatrouille> sequencePatrouille;
	unique_ptr<SequenceAlerte> sequenceAlerte;

	unique_ptr<RotateCamera> rotateAction;
	unique_ptr<ConditionAlerte> conditionAlerte;

	unique_ptr<AlerteAll> alerteAction;
};