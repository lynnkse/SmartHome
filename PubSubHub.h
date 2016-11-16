class Agent;
class Event;

class PubSubHub
{
public:
	PubSubHub();
	~PubSubHub();	
	void Subscribe(const Agent& _agent);
	void Publish(const Event& _event) const;

private:
	void operation=(const PubSubHub& _hub);
	PubSubHub(const PubSubHub& _hub);

	vectore<Agent> m_agents; //FIXME maybe something else???
};
