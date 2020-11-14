import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="menucli", # Replace with your own username
    version="2020.11.14",
    author="Claudio Corsi",
    author_email="clcorsi@yahoo.com",
    description="A simple command line menu module",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/ccorsi/learning/tree/menucli",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3',
)