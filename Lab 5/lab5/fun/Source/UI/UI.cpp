#include "UI/UI.h"

sf::ConvexShape UI::creatBoxForText(sf::Text t_text)
{

	sf::ConvexShape textBox;

	sf::FloatRect textSize = t_text.getLocalBounds();

	textBox.setPointCount(4);

	textBox.setPoint(0, { t_text.getPosition().x - (textSize.width / 2) - UI_WIDHT_SCALING , t_text.getPosition().y - (textSize.height / 2) - ( UI_HEIGHT_SCALING  /2 )});

	textBox.setPoint(1, { t_text.getPosition().x + (textSize.width / 2) + UI_WIDHT_SCALING,t_text.getPosition().y - (textSize.height / 2) - (UI_HEIGHT_SCALING / 2) });


	textBox.setPoint(2, { t_text.getPosition().x + (textSize.width / 2) + UI_WIDHT_SCALING,  t_text.getPosition().y + (textSize.height / 2) + UI_HEIGHT_SCALING });

	textBox.setPoint(3, { t_text.getPosition().x - (textSize.width / 2) - UI_WIDHT_SCALING, t_text.getPosition().y + (textSize.height / 2) + UI_HEIGHT_SCALING });

	return textBox;
}
