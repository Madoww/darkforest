#include "Shed.h"
int Cross::tilted_amount = 0;

Shed::Shed(int& scene)
:hatch_check(5),shadow1(&s1,Player::instance().getPointer()),shadow2(&s2,Player::instance().getPointer()),blood_check(4),wait_for_blood(200),shelfs(2),basement_shadow_map("shadowmap.txt"),scene(scene)
{
    background.setTexture(*TextureManager::get("inside"));
    background.setOrigin(background.getGlobalBounds().width/2,background.getGlobalBounds().height/2);
    background.setScale(8,8);
    background.setPosition(1200+background.getGlobalBounds().width/2-60*background.getScale().x,900-background.getGlobalBounds().height+100);
    background.setTextureRect(sf::IntRect(0,0,120,64));
    painting.setTexture(*TextureManager::get("painting"));
    painting.setPosition(900,260);
    painting.setScale(8,8);
    s1.setSize(sf::Vector2f(78*background.getScale().x,2*background.getScale().y));
    s2.setSize(sf::Vector2f(12*background.getScale().x,2*background.getScale().y));
    s1.setPosition(720,background.getPosition().y+background.getGlobalBounds().height/2-2*background.getScale().y+s1.getSize().y);
    s1.setFillColor(sf::Color::Red);
    s2.setFillColor(sf::Color::Red);
    s2.setPosition(s1.getPosition().x+30*background.getScale().x+s1.getSize().x,s1.getPosition().y);
    crosses.emplace_back(Cross(sf::Vector2f(700+400,500)));
    crosses.emplace_back(Cross(sf::Vector2f(800+400,200)));
    crosses.emplace_back(Cross(sf::Vector2f(820+400,400)));
    crosses.emplace_back(Cross(sf::Vector2f(930+400,300)));
    crosses.emplace_back(Cross(sf::Vector2f(630+400,320)));
    crosses.emplace_back(Cross(sf::Vector2f(1230+400,390)));
    crosses.emplace_back(Cross(sf::Vector2f(400+400,450)));
    //background.setColor(sf::Color(160,160,160));
    basement.setTexture(*TextureManager::get("basement"));
    basement.setScale(5,5);
    basement.setPosition(1253,742);
    basement.setColor(sf::Color(255,255,255,0));
    Player::instance().setPosition(sf::Vector2f(Player::instance().getPosition().x,590));
    if(!in_basement)
    hatch.setSize(sf::Vector2f(s2.getPosition().x-s1.getPosition().x,3));
    hatch.setPosition(s1.getPosition().x+s1.getSize().x+180,s1.getPosition().y-35);
    blood.setTexture(*TextureManager::get("blood_drop"));
    blood.setPosition(1115,544);
    blood.setScale(8,8);
    blood.setTextureRect(sf::IntRect(0,0,5,25));

    corridor.setTexture(*TextureManager::get("storage_room"));
    corridor.setScale(5,5);
    corridor.setPosition(700,374);

    door.setSize(sf::Vector2f(45*basement.getScale().x,73*basement.getScale().y));
    for(auto& shelf :shelfs)
    {
        shelf.setScale(10,10);
    }
    shelfs[0].setTexture(*TextureManager::get("shelf"));
    shelfs[1].setTexture(*TextureManager::get("shelf2"));
    shelfs[0].setPosition(900,300);
    shelfs[1].setPosition(1800,300);
    shadow1.setLength(3);
    shadow2.setLength(3);
    storage_room_overlay.setTexture(*TextureManager::get("storage_room_overlay"));
    storage_room_overlay.setScale(5,5);
    ladder.setSize(sf::Vector2f(17*corridor.getScale().x,94*corridor.getScale().y));
    ladder.setFillColor(sf::Color(111,111,111,111));
}

Shed::~Shed()
{
    //dtor
}

void Shed::draw(sf::RenderWindow& window)
{
    player.allow_stand = false;
    door.setPosition(sf::Vector2f(basement.getPosition().x+28*basement.getScale().x,basement.getPosition().y+22*basement.getScale().y));
    if(in_basement){

    window.draw(basement);
    window.draw(background);
    window.draw(painting);
    shadow1.update();
    shadow1.draw(window);
    shadow2.update();
    shadow2.draw(window);
    window.draw(blood);
    for(int i = 0; i<crosses.size(); i++)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && crosses[i].getGlobalBounds().contains(Click::instance().getPosition()))
        {crosses[i].tilt();is_tilted = true;}

        if(is_tilted)
        {
            if(rand()%10==1)
            crosses[i].tilt();
        }
        crosses[i].draw(window);
    }
    }
    else
    {

        window.draw(corridor);
        basement_shadow_map.draw(window);
        basement_shadow_map.update(corridor.getPosition());
        window.draw(storage_room_overlay);
        window.draw(ladder);
    }

}
void Shed::update()
{
    if(in_basement)
    {
            if(!Player::instance().is_animated)
        {
            if(door.getGlobalBounds().contains(Click::instance().getPosition()))
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    in_basement = false;
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !player.m_animated)
        {
            painting.move(Player::instance().speed,0);
            background.move(Player::instance().speed,0);
            s1.move(Player::instance().speed,0);
            s2.move(Player::instance().speed,0);
            for(int i = 0; i<crosses.size(); i++)
                crosses[i].move(Player::instance().speed,0);
            basement.move(Player::instance().speed,0);
            hatch.move(Player::instance().speed,0);
            blood.move(Player::instance().speed,0);
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || Player::instance().move_player == true) && !Player::instance().block_movement && !player.m_animated)
        {
            painting.move(-Player::instance().speed,0);
            background.move(-Player::instance().speed,0);
            s1.move(-Player::instance().speed,0);
            s2.move(-Player::instance().speed,0);
            for(int i = 0; i<crosses.size(); i++)
                crosses[i].move(-Player::instance().speed,0);
            basement.move(-Player::instance().speed,0);
            hatch.move(-Player::instance().speed,0);
            blood.move(-Player::instance().speed,0);
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.reset_animation();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))// && Cross::tilted_amount >= 1
        {
            open_hatch = true;
        }
        if(open_hatch == true && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Player::instance().move_player = true;
        }
        if(Player::instance().getPosition().x>s1.getPosition().x+s1.getSize().x && Player::instance().move_player == true && player.do_drop==false)
        {
            Player::instance().sit();
            Player::instance().move_player = false;
        }
        }
        if(Player::instance().is_sitting == true && player.do_drop==false && player.getTexture()!=TextureManager::get("player_drop") && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.drop();
            open_hatch =false;
        }
        if(Player::instance().getGlobalBounds().intersects(hatch.getGlobalBounds()) && player.getPosition().y<hatch.getPosition().y)
        {
            Player::instance().block_movement=true;
        }
        else
            Player::instance().block_movement=false;
        if(player.falling)
        {
            painting.move(falling_speed);
            background.move(falling_speed);
            s1.move(falling_speed);
            s2.move(falling_speed);
            for(int i = 0; i<crosses.size(); i++)
                crosses[i].move(falling_speed.x,falling_speed.y);
            basement.move(falling_speed);
            hatch.move(falling_speed);
            blood.move(falling_speed);
            camera.zoom(0.99);
        }
        hatch_check.update();
        if(open_hatch && hatch_check.getStatus())
        {
            background.setTextureRect(sf::IntRect(sourcex*120,0,120,64));
            if(sourcex<8)
            {
                basement.setColor(sf::Color(255,255,255,basement.getColor().a+255/8));
                sourcex++;
            }
            hatch_check.restart();
        }
        blood_check.update();
        wait_for_blood.update();
        if(blood_check.getStatus())
        {
            blood.setTextureRect(sf::IntRect(bloodx*5,0,5,25));
            if(bloodx<6)
            {
                bloodx++;
            }

            if(wait_for_blood.getStatus())
            {
                bloodx = 0;
                wait_for_blood.restart();
            }
            blood_check.restart();
        }
    }
    else
    {
        storage_room_overlay.setPosition(corridor.getPosition());
        ladder.setPosition(corridor.getPosition().x+370*corridor.getScale().x,corridor.getPosition().y);
        Flashlight::setLevel(255);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !player.m_animated)
        {
            corridor.move(player.speed,0);
            for(auto& shelf : shelfs)
                shelf.move(player.speed+3,0);
        }
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || player.move_player) && !player.m_animated)
        {
            corridor.move(-player.speed,0);
            for(auto& shelf : shelfs)
                shelf.move(-player.speed-3,0);
        }
        if(ladder.getGlobalBounds().contains(Click::instance().getPosition()))
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                camera.reset();
                scene++;
            }
        if(ladder.getGlobalBounds().contains(player.getPosition()))
            player.move_player = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            player.move_player = true;
    }
}
void Cross::draw(sf::RenderWindow& window)
{
    if(is_tilted && cross.getRotation()<180)
    {
        cross.setRotation(cross.getRotation()+1);
    }
    window.draw(cross);
}
void Shed::draw_over(sf::RenderWindow& window)
{
    if(!in_basement)
    {
        for(auto& shelf : shelfs)
        window.draw(shelf);
    }

}
void Cross::tilt()
{
    if(added == false)
    {
        tilted_amount++;
        added = true;
    }
    is_tilted = true;
}
