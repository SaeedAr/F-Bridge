# In The Name Of God
# ========================================
# [] File Name : l2.py
#
# [] Creation Date : 21-04-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
__author__ = 'Parham Alvani'

from ryu.base import app_manager


class L2Switch(app_manager.RyuApp):
    def __init__(self, *args, **kwargs):
        app_manager.RyuApp.__init__(self, args, kwargs)