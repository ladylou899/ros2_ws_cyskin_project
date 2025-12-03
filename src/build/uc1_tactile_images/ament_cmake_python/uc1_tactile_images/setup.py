from setuptools import find_packages
from setuptools import setup

setup(
    name='uc1_tactile_images',
    version='0.0.0',
    packages=find_packages(
        include=('uc1_tactile_images', 'uc1_tactile_images.*')),
)
