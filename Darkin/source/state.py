# state space in league of legends
class State:
    def __init__(self, state, action, reward, next_state):
        self.state = state
        self.action = action
        self.reward = reward
        self.next_state = next_state

    def __str__(self):
        return "State: " + str(self.state) + " Action: " + str(self.action) + " Reward: " + str(self.reward) + " Next State: " + str(self.next_state)

    def __repr__(self):
        return "State: " + str(self.state) + " Action: " + str(self.action) + " Reward: " + str(self.reward) + " Next State: " + str(self.next_state)

    def __eq__(self, other):
        return self.state == other.state and self.action == other.action and self.reward == other.reward and self.next_state == other.next_state

    def __hash__(self):
        return hash((self.state, self.action, self.reward, self.next_state))

    def get_state(self):
        return self.state

    def get_action(self):
        return self.action

    def get_reward(self):
        return self.reward

    def get_next_state(self):
        return self.next_state

    def set_state(self, state):
        self.state = state

    def set_action(self, action):
        self.action = action

    def set_reward(self, reward):
        self.reward = reward

    def set_next_state(self, next_state):
        self.next_state = next_state

    def get_state_action(self):
        return self.state, self.action

    def get_state_action_reward(self):
        return self.state, self.action, self.reward

    def get_state_action_reward_next_state(self):
        return self.state, self.action, self.reward, self.next_state

    def get_state_action_next_state(self):
        return self.state, self.action, self.next_state

    def get_action_reward(self):
        return self.action, self.reward

    def get_action_reward_next_state(self):
        return self.action, self.reward, self.next_state

    def get_reward_next_state(self):
        return self.reward, self.next_state

    def get_state_reward(self):
        return self.state, self.reward

    def get_state_reward_next_state(self):
        return self.state, self.reward, self.next_state

    def get_state_next_state(self):
        return self.state, self.next_state

    def get_action_next_state(self):
        return self.action, self.next_state


# Path: Darkin\source\state.py

