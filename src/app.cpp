#include "app.h"

app::app()
:m_window(sf::VideoMode(1920, 1080, 32), "The Dark Forest dev-build", sf::Style::Fullscreen),f(scene),gas(scene)
{
    m_window.setVerticalSyncEnabled(true);
    phone.setWindowSize((sf::Vector2f)m_window.getSize());
    scenes = {new GasStation(scene),new Forest(scene),new Shed()};
}

app::~app()
{
    if(m_window.isOpen())
    {
        m_window.close();
    }
}

void app::run()
{
    m_status = Status::Running;
    while (m_status != Status::CleaningUp)
	{
		sf::Event windowEvent;
		while (m_window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
				m_status = Status::CleaningUp;
            if(windowEvent.type == sf::Event::KeyPressed)
            {
                if(windowEvent.key.code == sf::Keyboard::Tab)
                {
                    if(phone.getStatus())
                        phone.setStatus(false);
                    else
                        phone.setStatus(true);
                }
                if(windowEvent.type == sf::Event::KeyPressed)
                {
                    if(windowEvent.key.code == sf::Keyboard::E)
                    {
                        if(inventory.getStatus())
                            inventory.close();
                        else
                            inventory.open();
                    }
                }
            }
		}
        phone.update();
        Click::instance().update(m_window);
        /*if(phone.getFlash())
            m_window.setMouseCursorVisible(false);
        else
            m_window.setMouseCursorVisible(true);*/
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            NoteSystem::instance().move(-2);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            NoteSystem::instance().move(2);
        }
        m_window.setView(camera.getView());
		m_window.clear(sf::Color(30,30,40));
		if(scene==Scene::GasStationScene)
            scenes[1]->draw(m_window);
		scenes[scene]->draw(m_window);
        player.draw(m_window);
            torch.run(m_window,50,phone.getFlash());
            torch.setScale(player.getPosition());
        m_window.setView(camera.getDefaultView());
        if(scene == Scene::GasStationScene || scene == Scene::Woods)
            leafs.draw(m_window);
        phone.draw(m_window);
        inventory.draw(m_window);
        dialog.draw(m_window);
        //items.update(m_window);
		m_window.display();
	}
}
